#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include "bsp/framebuffer.h"
#include "game.h"
#include "bsp/buttons.h"
#include "bsp/ws2812.h"
#include "bsp/terminal.h"
#include "ui.h"
#include "img/icons.h"
#include "bsp/config.h"
#include "img/titlescreen.h"
#include "bsp/eeprom.h"

static const uint16_t selected_color = RGB565(80, 80, 250);
static const uint16_t unavailable_color = RGB565(40, 40, 40);
static const uint16_t title_color = RGB565(255, 255, 0);
static const uint16_t description_color = RGB565(150, 150, 150);
static const uint16_t option_color = RGB565(150, 150, 150);

extern game_character_t crew[5];
extern int crew_count;
extern char game_stats[80];

char title_buffer[64];
char message_buffer[200];
char vote_text[512];
char vote_id[2];
char vote_options[4][64];
int vote_options_count = 0;

enum docking_state {
    none,
    syncing,
    welcome,
    voting,
    complete
};

enum docking_state dock_state;
absolute_time_t dock_time;

void parse_crew_string(char* str) {
    crew_count = 0;
    char* ptr = str;
    for (int i=0; i<5; ++i) {
        while(*ptr == ' ') ++ptr;
        if (strnlen(ptr, 21) < 20) {
            break;
        }
        if ((*ptr < 'A') || (*ptr > 'E')) {
            break;
        }
        crew[i].level=1;
        crew[i].specialty=*ptr++;
        strncpy(crew[i].id, ptr, 5);
        ptr+=5;
        memcpy(crew[i].name, ptr, 14);
        crew[i].skin_tone = *(uint16_t*)crew[i].id;
        ptr+=14;
        crew_count++;
    }
    if (crew_count == 5) {
        config_achievement(fully_crew);
        int unique=true;
        for (int i=0; i<4; ++i) {
            for (int j=i+1; j<5; ++j) {
                if (crew[i].specialty == crew[j].specialty){
                    unique=false;
                }
            }
        }
        if (unique) {
            config_achievement(unique_crew);
        }
    }
    if (crew_count == 0) {
        crew[0].level=1;
        crew[0].specialty = config_get_class();
        strncpy(crew[0].id, config_get_id(), 5);
        memcpy(crew[0].name, config_get_handle(), 15);
        crew_count = 1;
    }
}

void replace_char(char *str, char old_char, char new_char) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
        }
    }
}

int process_docking_commands() {
    char command[512];
    int processed = 0;

    while (terminal_pop_docking_command(command, sizeof(command))) {
        printf("Processing docking command: %s\n", command);
        if (strncmp(command, "$STATION", 8) == 0) {
            printf("station command recieved\n");
            vote_options_count = 0;
            if (dock_state != syncing) {
                dock_state = syncing;
                dock_time = get_absolute_time();
            }
            strncpy(message_buffer, command+9, sizeof(message_buffer));
            replace_char(message_buffer, '|', '\n');
            snprintf(command, sizeof(command), "$ID %c%5s%-14s%08X ", config_get_class(), config_get_id(), config_get_handle(), config_get_achievements());
            sign_message(command, sizeof(command));
            terminal_send(command);
            for (int i=0;i<3;++i) {
                char line[65]={0};
                eeprom_readbytes(64*(i+1),line, 64);
                if (line[0] == '$') {
                    terminal_send(line);
                }
            }
        } else if (strncmp(command, "$GAME", 5) == 0) {
            for (int i=0;i<3;++i) {
                char line[65]={0};
                eeprom_readbytes(64*(i+1),line, 64);
                if (strncmp(line, command, 16)==0) {
                    memset(line, 0, 64);
                    eeprom_readbytes(64*(i+1),line, 64);
                }
            }
        } else if (strncmp(command, "$DIALOG", 7) == 0) {
            strncpy(message_buffer, command+8, sizeof(message_buffer));
            printf("recieved DIALOG");
            //should we confirm reception?
        } else if (strncmp(command, "$OPTIONS", 8) == 0) {
            printf("recieved OPTIONS\n");
            vote_id[0] = *(command + 9);
            vote_id[1] = *(command + 10);
            char *at, *next = command+11;
            do {
                at = next +1 ;
                next = strchr(at, '|');
                if (next) {
                    *next = '\0';
                }
                strncpy(vote_options[vote_options_count++], at, sizeof(vote_options[0]));
            } while (next);
            //should we confirm reception?
        } else if (strncmp(command, "$EOL", 4) == 0) {
            printf("Docking complete\n");
            dock_state = welcome;
        } else if (strncmp(command, "$CREW", 5) == 0) {
            printf("Crew updated");
            const char *payload = command + 5;
            parse_crew_string((char *)payload);
        }
        else {
            printf("Bad uart command: %s\r\n", command);
        }
        processed++;
    }

    return processed;
}

void run_docking_welcome() {
    while (dock_state == welcome) {
        frame_clear();
        frame_draw_text(title_buffer, title_color, 30);
        frame_draw_text(message_buffer, description_color, 70);
        frame_refresh();
        int buttons = buttons_get_and_clear();
        if ((buttons & BUTTON_A) || (buttons & BUTTON_B)){
            dock_state = vote_options_count>0?voting:complete;
        }
        process_docking_commands();
    }
}

void run_docking_sync() {
    int dots = 0;
    char msg[64];
    while (dock_state == syncing) {
        snprintf(msg, sizeof(msg), "Docking.%c%c", dots>0?'.':' ', dots>1?'.':' ');
        dots = ++dots %3;
        frame_clear();
        frame_draw_text(msg, RGB565(0,200,0), 180);
        frame_refresh();
        process_docking_commands();
        sleep_ms(10);
        absolute_time_t end_time = get_absolute_time();
        int64_t elapsed_us = absolute_time_diff_us(dock_time, end_time);
        if (elapsed_us > (1000000 * 5)) { //pairing went wrong
            dock_state = none;
            printf("Timeout during docking\n");
        }
    }
}

void run_docking_vote() {
    buttons_clear();
    int selected_option = 0;

    while (dock_state == complete) {
        frame_clear();
        int y_offset = 30; // Initial y position
        y_offset += frame_draw_text(title_buffer, title_color, y_offset); // Yellow for POI name
        y_offset += frame_draw_text(vote_text, description_color, y_offset); // White color
        y_offset = 220; // Space between description and options
    
        for (int i=0; i< vote_options_count; ++i) {
            y_offset+= frame_draw_text(vote_options[i], i==selected_option?selected_color:option_color, y_offset);
        }
    
        frame_refresh();
        uint32_t keys = buttons_get_and_clear();

        if (keys & BUTTON_UP) {
            selected_option = selected_option == 0 ? vote_options_count -1 : selected_option - 1; // Wrap around options
        }
        else if (keys & BUTTON_DOWN) {
            selected_option = selected_option == vote_options_count -1 ? 0 : selected_option + 1; // Wrap around options
        }
        if (keys & BUTTON_A) {
            char resp[64];
            snprintf(resp, sizeof(resp), "$VOTE %5s %c%c %d ", config_get_id(), vote_id[0], vote_id[1], selected_option);
            sign_message(resp, sizeof(resp));
            terminal_send(resp);
            break; 
        }
        if (keys & BUTTON_B) {
            break; 
        }
        process_docking_commands();
    }
    dock_state = complete;
}

void run_docking_complete() {
    while (dock_state == complete) {
        frame_clear();
        frame_draw_text(title_buffer, title_color, 30);
        frame_draw_text(message_buffer, description_color, 70);
        frame_refresh();
        int buttons = buttons_get_and_clear();
        if ((buttons & BUTTON_A) || (buttons & BUTTON_B)){
            dock_state = none;
        }
        process_docking_commands();
    }
}

void run_achievement_screen() {
    int selected_index = 0;
    while (dock_state == none) {
        uint32_t unlocks = config_get_achievements();
        frame_clear();
        frame_draw_text("Achievements", title_color, 30); // Yellow color
        uint16_t color = RGB565(80,80,80);
        if (unlocks & (1<<selected_index)) {
            color = RGB565(180,180,180);
        }
        frame_draw_text(config_get_achievement_name(selected_index), color, 120); // White color
        int sx = selected_index % 8;
        int sy = selected_index / 8;
        frame_fill_rect(36 + sx * 36, 140 + sy * 36, 36, 36, selected_color); // Highlight selected character
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 8; col++) {
                const uint16_t* data = (unlocks & (1<<(row*8+col))) ? medal_image_data : locked_image_data;
                frame_draw_image(38 + col * 36, 142 + row * 36, data, 32, 32);
            }
        }
        char buffer[64];
        int count = config_get_achievement_count();
        snprintf(buffer, sizeof(buffer), "+%d credits", count * 150);
        frame_draw_text(buffer, RGB565(150,150,150), 330);
        frame_refresh();

        uint32_t keys = buttons_get_and_clear();
        if (keys & BUTTON_UP) {
            selected_index = (selected_index - 8 + 32) % 32;
        }
        if (keys & BUTTON_DOWN) {
            selected_index = (selected_index + 8) % 32;
        }
        if (keys & BUTTON_LEFT) {
            selected_index = (selected_index - 1 + 32) % 32;
        }
        if (keys & BUTTON_RIGHT) {
            selected_index = (selected_index + 1) % 32;
        }
        if (keys & BUTTON_B) {
            break;
        }
        process_docking_commands();
    }
}

void run_title_screen() {
    while (dock_state == none) {
        frame_clear();
        frame_draw_image(0,0,title_image_data,360,360);
        frame_refresh();
        int buttons = buttons_get_and_clear();
        if (buttons & BUTTON_A) {
            game_run();
        }
        else if (buttons & BUTTON_PRESS) {
            run_achievement_screen();
        }
        process_docking_commands();
    }
}

void run_main_loop() {
    switch (dock_state) {
    case none:
        run_title_screen();
        break;
    case welcome:
        run_docking_welcome();
        break;
    case syncing:
        run_docking_sync();
        break;
    case voting:
        run_docking_vote();
        break;
    case complete:
        run_docking_complete();
        break;
    default:
        printf("Unknown docking state: %d\n", dock_state);
        dock_state = none;
        break;
    }
}