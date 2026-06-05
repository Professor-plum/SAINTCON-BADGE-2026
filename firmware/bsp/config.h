#ifndef UNLOCKS_H
#define UNLOCKS_H
#include <stdint.h>

extern int game_running;

enum unlock {
    konima = 0,
    one_game,
    game_quota,
    game_event1,
    game_event2,
    fully_crew,
    unique_crew,
    social_1,
    social_2,
    re_flash,
    eeprom,
    hardcoded,
    uart_usb,
    uart_dock,
    crypto,
    boot,
    art1,
    art2,
    committee,
    venue1,
    venue2,
    venue3,
    unused1,
    unused2,
    communittees
};

int config_load();
void config_clear();
void config_set_handle(const char* name);
int config_submit(const char* key);
int config_unlock(enum unlock id);
int config_get_unlock_count();
int config_get_score();
void config_redeem_score();
uint32_t config_get_unlocks();
char* config_get_handle();
char config_get_class();


#endif