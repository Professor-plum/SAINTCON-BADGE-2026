#ifndef UNLOCKS_H
#define UNLOCKS_H
#include <stdint.h>

extern int game_running;

enum achievement {
    konima = 0,         //Obtained by entering the "Konima" unlock code (up up down down left right left right) 
    one_game,           //Obtained by completing your first mission
    game_quota,         //Obtained by reaching 5000 total score
    game_event1,        //Obtained by encountering "Relics of the First Builders" random event in the game
    game_event2,        //Obtained by encountering "The Obsidian Monolith" random event in the game
    fully_crew,         //Obtained by having a crew of 5 members
    unique_crew,        //Obtained by having a crew with all different specialties
    social_1,           //Obtained by being a crew member on another player's mission
    social_2,           //Obtained by being a crew member on lots of players' missions (exact threshold TBD)
    voter,              //Obtained by voting on at least 3 space station construction polls 
    re_flash,           //Obtained by reading the flash memory contents 
    eeprom,             //Obtained by reading the EEPROM contents
    hardcoded,          //Obtained by finding a hardcoded unlock in the firmware 
    uart_usb,           //Obtained by finding an unlock code via the USB UART interface
    uart_dock,          //Obtained by finding an unlock code via the docker port UART interface 
    crypto,             //Obtained by solving a cryptographic puzzle (exact details TBD)
    boot,               //Obtained by analyzing the self test screen and finding a hidden code or message
    art1,               //Obtained by analyzing the badge art circle patterns and finding a hidden code or message  
    art2,               //Obtained by analyzing the badge art constellations and finding a hidden code or message 
    committee,          //Obtained by social engineering an active member of the SAINTCON community 
    unused1,
    unused2,
    communities        // 10 additional achievements obtained by participating in community 
};

int config_load();
void config_clear();
void config_set_handle(const char* name);
int config_submit(const char* key);
int config_achievement(enum achievement id);
int config_get_achievement_count();
int config_get_score();
void config_redeem_score();
uint32_t config_get_achievements();
char* config_get_handle();
char config_get_class();
char* config_get_class_name();
char* config_get_achievement_name(enum achievement id);
void config_get_id(char* out);


#endif