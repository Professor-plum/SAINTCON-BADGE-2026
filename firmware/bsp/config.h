#ifndef UNLOCKS_H
#define UNLOCKS_H
#include <stdint.h>

extern int game_running;

int config_load();
void config_clear();
void config_set_handle(const char* name);
int config_unlock(const char* key);
int config_get_unlock_count();
int config_get_score();
void config_redeem_score();
uint32_t config_get_unlocks();
char* config_get_handle();
char config_get_class();


#endif