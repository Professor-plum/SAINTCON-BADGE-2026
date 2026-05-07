#include "game.h"
#include "framebuffer.h"
#include "buttons.h"
#include <stdio.h>
#include "pico/rand.h"
#include "pico/stdlib.h"
#include "hexutils.h"
#include "img/nebula.h"
#include "img/astroids.h"
#include "img/poi.h"
#include "img/rocket.h"
#include "img/ui.h"
#include <string.h>
#include "bsp/config.h"

const int hex_size = 36;
const int fuel_cost = 3; // fuel cost per unit


game_config_t config = {
    .max_fuel = 10,
    .max_hull = 5,
    .max_cargo = 16
};
game_state_t state;

int game_running = false;

int g_seed = 0;
Point screen_pos;

extern const event_t random_events[];
extern const unsigned int random_event_count;

static const uint16_t selected_color = RGB565(250, 250, 250);
static const uint16_t unavailable_color = RGB565(40, 40, 40);
static const uint16_t title_color = RGB565(255, 255, 0);
static const uint16_t description_color = RGB565(150, 150, 150);
static const uint16_t option_color = RGB565(150, 150, 150);

void pseudo_random_init(int seed) {
    g_seed = seed;
}

int psuedo_random() {
    // Simple linear congruential generator (LCG) for demonstration
    g_seed = (g_seed * 1664525 + 1013904223) % 0xFFFFFFFF;
    return g_seed;
}

uint16_t get_rand_skin_tone() {
    // Generate a random skin tone in RGB565 format
    uint8_t r = (get_rand_32() % 128) + 64; // 64-191 for better visibility
    uint8_t g = (get_rand_32() % 128) + 64;
    uint8_t b = (get_rand_32() % 128) + 64;
    return RGB565(r, g, b);
}

Hex get_random_hex(int distance) {
    int ring_size = 6 * distance;
    Hex ring[ring_size];
    int index = 0;
    for (int q=-distance; q <= distance; q++) {
        for (int r=-distance; r <= distance; r++) {
            if (abs(q) + abs(r) + abs(-q-r) == 2*distance) {
                ring[index++] = (Hex){q, r};
            }
        }
    }
    index = get_rand_32() % ring_size;
    return ring[index];
}

enum tiletype get_hex_type(Hex hex) {
    if (hex.q == 0 && hex.r == 0) return TILE_HOME;
    if (hex_equal(state.nebula, hex)) return TILE_NEBULA;
    if ((state.nebula.q+1) == hex.q && state.nebula.r == hex.r) return TILE_NEBULA;
    if ((state.nebula.q+1) == hex.q && (state.nebula.r-1) == hex.r) return TILE_NEBULA;
    for (int i = 0; i < 6; i++) {
        if (hex_equal(state.astroids[i], hex)) return TILE_ASTROID;
    }
    for (int i = 0; i < 10; i++) {
        if (hex_equal(state.poi[i], hex)) return TILE_POI;
    }
    return TILE_EMPTY;
}

const char* crew_names[5] = {"Astra", "Zara", "Kai", "Luna", "Jax"};

void game_init() {
    int unlocks = config_get_unlock_count();
    config.max_fuel = 8 + (unlocks+2)>>2; // Increase max fuel every 4 unlocks
    config.max_hull = 3 + (unlocks)>>2; // Increase max hull every 4 unlocks
    config.max_cargo = 8 + (unlocks+1)>>1; // Increase max cargo every 2 unlocks
    state.seed = get_rand_32();
    Hex t;
    do {
        t= get_random_hex(4);
    } while (get_hex_type(t)!=TILE_EMPTY);
    state.nebula = t;

    for (int i = 0; i < 6; i+=2) {
        do {
            t = get_random_hex(i + 3);
        } while (get_hex_type(t)!=TILE_EMPTY);
        state.astroids[i] = t;
        Hex at = state.astroids[i];
        Hex near[6] = {{at.q,at.r-1}, {at.q+1,at.r-1}, {at.q+1,at.r}, {at.q,at.r+1}, {at.q-1,at.r+1}, {at.q-1,at.r}};
        for (int j=0; j<6; ++j) {
            t = near[j];
            int o = get_rand_32()%6;
            near[j] = near[o];
            near[o] = t;
        }
        for (int j=0; j<6; ++j) {
            if (get_hex_type(near[j])==TILE_EMPTY) {
                state.astroids[i+1] = near[j];
                break;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        int dist = i*2/3 + 4; // Distance from center increases with index
        do {
            t = get_random_hex(dist);
        } while (get_hex_type(t)!=TILE_EMPTY);
        state.poi[i] = t;
        state.poi_market_rate[i] = (get_rand_32() % 5) + dist * 3; // Market rate between 1 and 5
    }
    state.poi_market_rate[8] *= 2.5; 
    state.poi_market_rate[6] *= 2;
    state.poi_market_rate[4] *= 3;
    state.poi_market_rate[4] /= 4;
    state.poi_market_rate[2] /= 2;  
    state.player.q = 0;
    state.player.r = 0;
    state.heading = 0;
    state.hull = config.max_hull;
    state.fuel = config.max_fuel;
    state.cargo = config.max_cargo;
    state.reputation = 0;
    state.xp = 0;
    Point at = hex_to_pixel(state.player, hex_size);
    screen_pos.x = LCD_WIDTH/2 - at.x;
    screen_pos.y = LCD_HEIGHT/2 - at.y;

    state.credits = 0;
    for (int i = 0; i < 5; i++) {
        state.crew[i].specialty = get_rand_32() % 5; // 0 = Pilot, 1 = Engineer, 2 = Scientist, 3 = Soldier
        state.crew[i].level = (get_rand_32() % 5) + 1; // Level between 1 and 5
        strncpy(state.crew[i].name, crew_names[i], sizeof(state.crew[i].name));
    }
    state.crew_count = 5;
}

void game_draw_character(int x, int y, const game_character_t* character) {
    uint16_t color = character->skin_tone;
    //frame_fill_rect(x+1, y+3, 5, 3, color); // Draw a simple square for the character's face
    //frame_draw_pixel(x+2, y+3, RGB565(0,0,0)); // Left eye
    //frame_draw_pixel(x+4, y+3, RGB565(0,0,0)); // Right eye
    frame_draw_image(x, y, player_img_data[character->specialty], 14, 16); // Placeholder for character image
    // In a real implementation, you would draw the character based on their specialty and level
}

void game_draw_ui() {
    const uint16_t hull_color = RGB565(0,0,150);
    const uint16_t fuel_color = RGB565(0,150,150);
    
    frame_draw_line(2, LCD_HEIGHT/2 - 27, 2, LCD_HEIGHT/2-20, fuel_color);
    frame_draw_line(2, LCD_HEIGHT/2 - 27, 5, LCD_HEIGHT/2-27, fuel_color);
    frame_draw_line(2, LCD_HEIGHT/2 - 24, 4, LCD_HEIGHT/2-24, fuel_color);
    for (int i=0; i<state.fuel; ++i) {
        frame_fill_rect(0, LCD_HEIGHT/2 -19 + i*4, 10, 3, fuel_color);
    }
    frame_draw_line(LCD_WIDTH - 8, LCD_HEIGHT/2 - 27, LCD_WIDTH - 8, LCD_HEIGHT/2 -21, hull_color);
    frame_draw_line(LCD_WIDTH - 3, LCD_HEIGHT/2 - 27, LCD_WIDTH - 3, LCD_HEIGHT/2 -21, hull_color);
    frame_draw_line(LCD_WIDTH - 8, LCD_HEIGHT/2 - 24, LCD_WIDTH - 3, LCD_HEIGHT/2-24, hull_color);
    for (int i=0; i<state.hull; ++i) {
        frame_fill_rect(LCD_WIDTH - 10, LCD_HEIGHT/2 -19 + i * 8, 10, 6, hull_color);
    }

    for (int i=0; i<state.crew_count; ++i) {
        game_draw_character(180-35 + i*14, LCD_HEIGHT-40, &state.crew[i]);
    }

    for (int i=0; i<state.cargo; ++i) {
        frame_fill_rect(LCD_WIDTH /2 - 10 - 6*(i%8), LCD_HEIGHT - 22 + 6*(i/8), 4, 4, RGB565(150, 75, 0)); // Brown color for cargo
    }

    char credits_str[20];
    snprintf(credits_str, sizeof(credits_str), "$%d", state.credits);
    frame_draw_string(LCD_WIDTH/2 + 5, LCD_HEIGHT - 8, credits_str, RGB565(0, 0, 200)); // blue color
}

void game_show_message(const char* title, const char* message) {
    frame_clear();
    frame_draw_text(title, title_color, 30); // Yellow color
    frame_draw_text(message, description_color, LCD_HEIGHT/3); // White color
    game_draw_ui();
    frame_refresh();
}

bool game_is_option_available(const event_option_t* option) {
    // Check crew requirements
    if (option->requirements & EV_FLAG_REQUIRES_PILOT) {
        for (int i=0; i<5; ++i) {
            if (state.crew[i].specialty == CREW_SPECIALTY_PILOT && state.crew[i].level >= option->required_count) {
                return true;
            }
        }
        return false;
    }
    if (option->requirements & EV_FLAG_REQUIRES_ENGINEER) {
        for (int i=0; i<5; ++i) {
            if (state.crew[i].specialty == CREW_SPECIALTY_ENGINEER && state.crew[i].level >= option->required_count) {
                return true;
            }
        }
        return false;
    }
    if (option->requirements & EV_FLAG_REQUIRES_SCIENTIST) {
        for (int i=0; i<5; ++i) {
            if (state.crew[i].specialty == CREW_SPECIALTY_SCIENTIST && state.crew[i].level >= option->required_count) {
                return true;
            }
        }
        return false;
    }
    if (option->requirements & EV_FLAG_REQUIRES_SOLDIER) {
        for (int i=0; i<5; ++i) {
            if (state.crew[i].specialty == CREW_SPECIALTY_SOLDIER && state.crew[i].level >= option->required_count) {
                return true;
            }
        }
        return false;
    }
    if (option->requirements & EV_FLAG_REQUIRES_MEDIC) {
        for (int i=0; i<5; ++i) {
            if (state.crew[i].specialty == CREW_SPECIALTY_MEDIC && state.crew[i].level >= option->required_count) {
                return true;
            }
        }
        return false;
    }

    // Check resource requirements
    if (option->requirements & EV_FLAG_REQUIRES_CARGO) {
        if (state.cargo < option->required_count) return false;
    }
    if (option->requirements & EV_FLAG_REQUIRES_CREDITS) {
        if (state.credits < option->required_count) return false;
    }
    if (option->requirements & EV_FLAG_REQUIRES_FUEL) {
        if (state.fuel < option->required_count) return false;
    }

    return true;
}

void game_draw_event(const event_t* event, int selected_index) {
    frame_clear();
    int y_offset = 30;
    y_offset += frame_draw_text(event->title, title_color, y_offset); // Yellow color
    y_offset += frame_draw_text(event->description, description_color, y_offset); // White color
    y_offset = 230; // Space between description and options
    for (int i = 0; i < event->option_count; i++) {
        int color = (i == selected_index) ? selected_color : option_color;
        if (!game_is_option_available(&event->options[i])) {
            color = unavailable_color; // Dim unavailable options
        }
        y_offset += frame_draw_text(event->options[i].description, color, y_offset) + 2; // Space between options
    }
    game_draw_ui();
    frame_refresh();
}

void game_show_outcome(const char* message, uint8_t effects_count, const event_effect_t* effects) {
    frame_clear();
    int y_offset = 60 + frame_draw_text(message, description_color, 60); // White color
    y_offset = 220; // Space between description and effects
    for (int i = 0; i < effects_count; i++) {
        char effect_str[50];
        const char* effect_type;
        switch (effects[i].type) {
            case EV_EFFECT_HULL: effect_type = "Hull"; break;
            case EV_EFFECT_FUEL: effect_type = "Fuel"; break;
            case EV_EFFECT_CREDITS: effect_type = "Credits"; break;
            case EV_EFFECT_CREW: effect_type = "Crew"; break;
            case EV_EFFECT_CARGO: effect_type = "Cargo"; break;
            case EV_EFFECT_REPUTATION: effect_type = "Reputation"; break;
            case EV_EFFECT_XP: effect_type = "XP"; break;
            default: effect_type = "Unknown"; break;
        }
        int color = effects[i].value > 0 ? RGB565(0, 255, 0) : RGB565(255, 0, 0); // Green for positive, Red for negative
        if (effects[i].type != EV_EFFECT_CREW) {
            snprintf(effect_str, sizeof(effect_str), "%s: %d", effect_type, effects[i].value);
        } else {
            //Handle crew changes with more detail here
            if (effects[i].value < 0) {
                    snprintf(effect_str, sizeof(effect_str), "Crew lost: ");
                    for (int j=0; j>effects[i].value; --j) {
                        int idx = get_rand_32() % state.crew_count;
                        state.crew_count--;
                        state.crew[idx] = state.crew[state.crew_count]; // Remove crew member by replacing with last
                        if (j < 0) {
                            strncat(effect_str, ", ", sizeof(effect_str) - strlen(effect_str) - 1);
                        }
                        strncat(effect_str, state.crew[idx].name, sizeof(effect_str) - strlen(effect_str) - 1);
                    }       
            }
            else {
                if (state.crew_count < 5) {
                    state.crew[state.crew_count].specialty = get_rand_32() % 5; // Random specialty
                    state.crew[state.crew_count].level = 3; // Starting level for new crew
                    strncpy(state.crew[state.crew_count].name, crew_names[state.crew_count], sizeof(state.crew[state.crew_count].name));
                    snprintf(state.crew[state.crew_count].name, sizeof(state.crew[state.crew_count].name), "%s joins your crew", state.crew[state.crew_count].name); 
                    state.crew_count++;
                } else {
                    strncat(effect_str, "Crew full, cannot add more", sizeof(effect_str) - strlen(effect_str) - 1);
                    color = RGB565(255, 255, 0); // Yellow color for failed crew addition
                }
            }
        }
        frame_draw_string_centered(y_offset + i * 30, effect_str, color); // Red color for effects 
   }   
    frame_refresh();
}


void game_run_event(const event_t* event) {

    //First, show the event description
    buttons_clear();

    int selected_option = -1;
    do {
        selected_option = (selected_option + 1) % event->option_count;
    } while (!game_is_option_available(&event->options[selected_option]));
    printf("Running event: %s\n", event->title);   
    while (1) {
        game_draw_event(event, selected_option);
        uint32_t keys = buttons_get_and_clear();

        if (keys & BUTTON_UP) {
            do {
                selected_option = (selected_option - 1 + event->option_count) % event->option_count;
            } while (!game_is_option_available(&event->options[selected_option]));
        }
        if (keys & BUTTON_DOWN) {
            do {
                selected_option = (selected_option + 1) % event->option_count;
            } while (!game_is_option_available(&event->options[selected_option]));
        }
        if (keys & BUTTON_PRESS) {
            break; // Option selected
        }
        if (keys & BUTTON_2) {
            break;
        }
    }

    int rand_range = 0;
    for (int i = 0; i < event->options[selected_option].outcome_count; i++) {
        rand_range += event->options[selected_option].outcomes[i].chance;
    }
    const event_outcome_t* selected_outcome;
    if (rand_range == 0) {
        selected_outcome = &event->options[selected_option].outcomes[0];
    } else {
        int rand_value = get_rand_32() % rand_range;
        int cumulative_chance = 0;
        for (int i = 0; i < event->options[selected_option].outcome_count; i++) {
            cumulative_chance += event->options[selected_option].outcomes[i].chance;
            if (rand_value < cumulative_chance) {
                selected_outcome = &event->options[selected_option].outcomes[i];
                break;
            }
        }
    }

    // Show outcome description
    game_show_outcome(selected_outcome->description, selected_outcome->effect_count, selected_outcome->effects);
    for (int i = 0; i < selected_outcome->effect_count; i++) {
        switch (selected_outcome->effects[i].type) {
            case EV_EFFECT_HULL: state.hull += selected_outcome->effects[i].value; break;
            case EV_EFFECT_FUEL: state.fuel += selected_outcome->effects[i].value; break;
            case EV_EFFECT_CREDITS: state.credits += selected_outcome->effects[i].value; break;
            case EV_EFFECT_CREW: {
                // Handled in game_show_outcome for more detailed crew changes, so we can skip applying it here
            } break;
            case EV_EFFECT_CARGO: state.cargo += selected_outcome->effects[i].value; break;
            case EV_EFFECT_REPUTATION: state.reputation += selected_outcome->effects[i].value; break;
            case EV_EFFECT_XP: state.xp += selected_outcome->effects[i].value; break;
        }
    }
    //wait for player to press a button to continue
    buttons_clear();
    while (buttons_get_and_clear() == 0) {
        sleep_ms(100);
    }

}

void game_draw_map(int x, int y, int xoff, int yoff) {
    pseudo_random_init(state.seed);
    for (int i = 0; i < 2000; i++) {
        int xt = psuedo_random() % 700;
        int yt = psuedo_random() % 700;
        int brightness = abs(psuedo_random() % 256);
        frame_draw_pixel(x+xt, y+yt, RGB565(brightness, brightness, brightness)); // White star
    }

    frame_draw_hexagon_grid(x, y, hex_size, RGB565(30,30,30));

    Point at = hex_to_pixel(state.nebula, hex_size);
    frame_draw_image(x+at.x-32, y+at.y-62, nebula_image_data, 128, 128);
    for (int i=0; i<6; ++i) {
        at = hex_to_pixel(state.astroids[i], hex_size);
        frame_draw_image(x+at.x-33, y+at.y-31, astroid_image_data[i], 66, 63);
    }
    const uint16_t sineLookupTable[] = {
        1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1,
        1, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0};
    absolute_time_t current_time = get_absolute_time();
    uint32_t milliseconds_since_boot = to_ms_since_boot(current_time);
    int poi_offset = sineLookupTable[(milliseconds_since_boot>>6)%32];
    for (int i = 0; i < 9; i++) {
        at = hex_to_pixel(state.poi[i], hex_size);
        frame_draw_image(x+at.x-16, y+at.y-16+poi_offset, poi_image_data[i], 32, 32);
    }
    at = hex_to_pixel((Hex){0,0}, hex_size);
    frame_draw_image(x+at.x-31, y+at.y-28, station_image_data, 62, 48); // Space station at center

    if ((xoff == 0) && (yoff == 0)) {
        Hex hex = pixel_to_hex(LCD_WIDTH/2-x, LCD_HEIGHT/2-y, hex_size);
        Point hex_pixel = hex_to_pixel(hex, hex_size);
        int distance = hex_distance(hex, state.player);
        if (distance == 0){
            frame_draw_hexagon(x+hex_pixel.x, y+hex_pixel.y, hex_size, RGB565(200, 200, 200));
        }
        else if (distance > 0) {
            uint16_t color = distance < 2 ? RGB565(0, 200, 0) : RGB565(200, 0, 0);
            frame_draw_hexagon(x+hex_pixel.x, y+hex_pixel.y, hex_size, color);
        }
    }

    at = hex_to_pixel(state.player, hex_size);
    frame_draw_image(x+at.x-16+xoff, y+at.y-16+yoff, rocket_image_data[state.heading % 6], 32, 32); // Player ship
    game_draw_ui();
}

void game_run_map() {
    while (true) {
        frame_clear();
        game_draw_map(screen_pos.x, screen_pos.y, 0, 0);
        frame_refresh();
        int buttons = buttons_get_raw();
        if (buttons & BUTTON_UP) {
            screen_pos.y += 4;
        }
        if (buttons & BUTTON_DOWN) {
            screen_pos.y -= 4;
        }
        if (buttons & BUTTON_LEFT) {
            screen_pos.x -= 4;
        }
        if (buttons & BUTTON_RIGHT) {
            screen_pos.x += 4;
        }
        if (buttons & BUTTON_PRESS) {
            int mframes=30;
            Hex hex = pixel_to_hex(LCD_WIDTH/2-screen_pos.x, LCD_HEIGHT/2-screen_pos.y, hex_size);
            int distance = hex_distance(hex, state.player);
            if (distance == 1) {
                Point hex_pixel = hex_to_pixel(hex, hex_size);
                state.heading = hex_get_heading(state.player, hex);
                Point player_at = hex_to_pixel(state.player, hex_size);
                int dx = (hex_pixel.x - player_at.x);
                int dy = (hex_pixel.y - player_at.y);
                for (int i=1; i<=mframes; ++i) {
                    frame_clear();
                    game_draw_map(screen_pos.x, screen_pos.y, dx*i/mframes, dy*i/mframes);
                    frame_refresh();
                }
                if (get_hex_type(state.player) == TILE_ASTROID) {
                    state.hull-= get_rand_32() % 2 + 1; // Take some damage if leaving an astroid tile
                } 
                if (get_hex_type(hex) == TILE_ASTROID) {
                    state.hull-= get_rand_32() % 2 + 1; // Take some damage if entering an astroid tile
                }
                state.player = hex;
                state.fuel--; // Consume fuel for movement
                return;
            }
        }
    }
}

event_t* get_tile_event(enum tiletype type) {
    switch (type) {
        case TILE_EMPTY:
            if ((get_rand_32() % 3) == 0) {
                //TODO: return random event
            }
            break;
        case TILE_NEBULA:
            //TODO return random nebula event
            break;
        case TILE_ASTROID:
            //TODO return random astroid event
        case TILE_HOME:
            //Is this an event or something else?
            break;
        case TILE_POI:
            //TODO: return random POI event
            break;
    }
}

int game_market_item_select(int selected_option, uint32_t keys) {
    if (keys & BUTTON_UP) {
        selected_option = (selected_option - 1 + 3) % 3; // Assuming 3 market options: Sell, Refuel, Leave
    }
    else if (keys & BUTTON_DOWN) {
        selected_option = (selected_option + 1) % 3 ; // Assuming 3 market options: Sell, Refuel, Leave
    }
    if ((selected_option == 0) && state.cargo <= 0) {
        return game_market_item_select(selected_option, keys); // Move to next item
    } else if ((selected_option == 1) && state.fuel >= config.max_fuel) {
        return game_market_item_select(selected_option, keys); // Move to next item
    } else if ((selected_option == 1) && state.credits < fuel_cost) {
        return game_market_item_select(selected_option, keys); // Move to next item
    } return selected_option;
}


void game_draw_market(const char* poi_name, const char* market_data, int market_rate, int selected_option) {
    frame_clear();
    int y_offset = 60; // Initial y position
    frame_draw_text(poi_name, title_color, 20); // Yellow for POI name
    y_offset += frame_draw_text(market_data, description_color, y_offset); // White color
    y_offset = 220; // Space between description and options
    char sell_option[50];
    char refuel_option[50];
    char leave_option[50];
    uint16_t sell_color = state.cargo > 0 ? option_color : unavailable_color;
    uint16_t refuel_color = (state.fuel < config.max_fuel && state.credits >= fuel_cost) ? option_color : unavailable_color;
    uint16_t leave_color = option_color;
    if (selected_option == 0) {
        sell_color = selected_color;
    } else if (selected_option == 1) {
        refuel_color = selected_color;
    } else if (selected_option == 2) {
        leave_color = selected_color;
    }
    snprintf(sell_option, sizeof(sell_option), "Sell 1 Cargo for %d credits", market_rate);
    snprintf(refuel_option, sizeof(refuel_option), "Refuel (%d credits)", fuel_cost * (config.max_fuel - state.fuel));
    snprintf(leave_option, sizeof(leave_option), "Leave Market");
    y_offset += frame_draw_text(sell_option, sell_color, y_offset); // Space between options
    y_offset += frame_draw_text(refuel_option, refuel_color, y_offset);
    y_offset += frame_draw_text(leave_option, leave_color, y_offset);
    game_draw_ui();
    frame_refresh();
}

const char* market_data[10] = {
    "Emergency shortages across the colony. Dockmasters are authorizing extreme premiums. Your cargo could stabilize critical systems.",
    "Trade lanes have been disrupted and reserves are nearly exhausted. Buyers are scrambling to secure contracts before competitors do.",
    "Rapid expansion and infrastructure growth are driving intense demand. Merchants are offering incentives for immediate delivery.",
    "Commercial activity is accelerating. Cargo is moving quickly through the port and profit margins are strong.",
    "Steady demand across multiple sectors. Traders are willing to pay above standard rates for reliable suppliers."
    "Trade flows normally. Buyers and sellers are balanced and pricing reflects typical interstellar averages.",
    "Recent shipments have satisfied most needs. Buyers are negotiating cautiously and inventory turnover is slower.",
    "Warehouses are filling faster than goods are leaving. Merchants are reluctant to take on additional stock.",
    "Trade convoys have saturated the market. Buyers are delaying purchases while waiting for prices to fall further.",
    "Storage bays are overflowing and automated brokers are rejecting new contracts. Only deeply discounted cargo is moving."
};

const char* get_market_data(int market_rate) {
    if (market_rate >= 30) {
        return market_data[0];
    } else if (market_rate >= 25) {
        return market_data[1];
    } else if (market_rate >= 21) {
        return market_data[2];
    } else if (market_rate >= 16) {
        return market_data[3];
    } else if (market_rate >= 12) {
        return market_data[4];
    } else if (market_rate >= 9) {
        return market_data[5];
    } else if (market_rate >= 6) {
        return market_data[6];
    } else if (market_rate >= 4) {
        return market_data[7];
    } else if (market_rate >= 2) {
        return market_data[8];
    }
    return market_data[9];
}

void game_run_market() {

    buttons_clear();

    int selected_option = 0;
    int poi_idx = -1;
    for (int i=0; i<10; ++i) {
        if (hex_equal(state.poi[i], state.player)) {
            poi_idx = i;
            break;
        }
    }
    const char* market_data = NULL;
    while (true)
    {
        int market_rate = state.poi_market_rate[poi_idx >= 0 ? poi_idx : 0]; // Get market rate for current POI, or default if not found
        if (market_data == NULL) {
            market_data = get_market_data(market_rate);
        }
        while (1) {
            game_draw_market(poi_names[poi_idx >= 0 ? poi_idx : 0], market_data, market_rate, selected_option);
            uint32_t keys = buttons_get_and_clear();

            if (keys & BUTTON_UP) {
                selected_option = game_market_item_select(selected_option, keys);
            }
            else if (keys & BUTTON_DOWN) {
                selected_option = game_market_item_select(selected_option, keys);
            }
            if (keys & BUTTON_PRESS) {
                break; // Option selected
            }
        }
        if (selected_option == 0) {
            // Handle selling supplies
            int sell_amount = 1; 
            if (state.cargo <= 0) {
                selected_option = game_market_item_select(selected_option, BUTTON_DOWN);
                break;
            }
            state.cargo -= sell_amount;
            state.credits += sell_amount * market_rate; // Example pricing formula
            state.poi_market_rate[poi_idx >= 0 ? poi_idx : 0] -= state.poi_market_rate[poi_idx >= 0 ? poi_idx : 0] * 0.15; // Market rate decreases by 15% after selling
            if (state.poi_market_rate[poi_idx >= 0 ? poi_idx : 0] < 1) {
                state.poi_market_rate[poi_idx >= 0 ? poi_idx : 0] = 1; // Minimum market rate
            }
        } else if (selected_option == 1) {
            // Handle refueling
            int refuel_amount = config.max_fuel - state.fuel; // Refuel up to max fuel of 10
            if (refuel_amount > 0) {
                if (state.credits < refuel_amount * fuel_cost) {
                    refuel_amount = state.credits / fuel_cost; // Can't refuel more than you can afford
                } 
                state.fuel += refuel_amount;
                state.credits -= refuel_amount * fuel_cost; // Example pricing formula
            }
        } else if (selected_option == 2) {
            break; // Leave market
        }
    }
}


void game_run() {
    game_running = true;
    game_init();
    while (game_running) {
        game_run_map();
        enum tiletype tiletype = get_hex_type(state.player);
        buttons_clear();
        switch (tiletype)
        {
        case TILE_EMPTY:
        case TILE_ASTROID:
            if ((get_rand_32() % 3) == 0) {
                int idx = get_rand_32() % random_event_count;
                const event_t* event = &random_events[idx];
                if (event) {
                    game_run_event(event);
                }
            }
            break;
        case TILE_NEBULA:
            //TODO return random nebula event
            break;
        case TILE_HOME:
            buttons_clear();
            if ((state.credits >= 100)) {
                char message[300];
                int score = state.credits + state.reputation * 10 + state.xp * 5 + state.crew_count * 20;
                snprintf(message, sizeof(message), "Congratulations, Captain! You have completed your mission with a score of %d. Your credits, reputation, experience, and crew have all contributed to your success.\n\nDock at a space station to redeem your credits and save your progress.", score);
                game_show_message("Mission Complete!", message);
                while (buttons_get_and_clear() == 0) {
                    sleep_ms(100);
                }
                return;
            } else if (state.cargo > 0) {
                game_show_message("", "You are back at the space station. Sell some cargo to get more credits to complete your mission.");
                while (buttons_get_and_clear() == 0) {
                    sleep_ms(100);
                }
            }
            else {
                game_show_message("Mission Failed", "You are back at the space station, but you have no cargo left to sell.");
                while (buttons_get_and_clear() == 0) {
                    sleep_ms(100);
                }
            }
            state.cargo = config.max_cargo; // Restock cargo at home base
            state.fuel = config.max_fuel; // Refuel at home base
            //state.hull = config.max_hull; // Repair hull at home base
            break;
        case TILE_POI:
            game_run_market();
            break;
        }
        if (state.hull <= 0) {
            game_show_message("Hull Failure", "Structural integrity collapses under mounting stress. The hull fractures, then shatters. Warning alarms cut out mid-scream. For a brief moment, your ship becomes stardust; indistinguishable from the debris it joins. Mission terminated.");
            while (buttons_get_and_clear() == 0) {
                sleep_ms(100);
            }
            game_running = false;
        }
        if (state.fuel <= 0) {
            game_show_message("Fuel Exhausted", "Your engines fall silent as the last reserves burn away. You drift between the stars, momentum carrying you nowhere. Distress signals echo into the void... but no one answers. Your journey ends in quiet orbit around nothing.");
            while (buttons_get_and_clear() == 0) {
                sleep_ms(100);
            }
            game_running = false;
        }
        if (state.crew_count <= 0) {
            game_show_message("Crew Lost", "The final crew member falls silent. No voices remain on the comms. Systems continue their routines, but no one is left to guide them. Your ship drifts on; a perfectly functioning vessel with no one aboard. Mission abandoned.");
            while (buttons_get_and_clear() == 0) {
                sleep_ms(100);
            }
            game_running = false;
        }
    }
}