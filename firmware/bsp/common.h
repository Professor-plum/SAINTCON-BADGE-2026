#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>

void pseudo_random_init(int seed);
int psuedo_random();
void sign_message(char* message, size_t msg_size);

typedef struct {
    uint8_t specialty;
    uint8_t level;
    uint16_t skin_tone; // RGB565 color for character skin tone
    unsigned char id[6];
    char name[15];
} game_character_t;

#endif //COMMON_H
