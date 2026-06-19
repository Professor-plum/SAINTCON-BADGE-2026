#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "base64.h"
#include "bsp_komihash.h"
#include "config.h"

int g_seed = 0;
uint64_t signkey = 0;

void pseudo_random_init(int seed) {
    g_seed = seed;
}

int psuedo_random() {
    // Simple linear congruential generator (LCG) for demonstration
    g_seed = (g_seed * 1664525 + 1013904223) % 0xFFFFFFFF;
    return g_seed;
}

void sign_message(char* message, size_t msg_size) {
    char sig[12];
    if (signkey == 0) {
        base64_decode(config_get_id(), (uint8_t*)&signkey, sizeof(uint64_t));
    }
    
    size_t len = strlen(message);
    uint64_t hash = komihash(message, len, signkey);
    base64_encode((uint8_t*)&hash, sizeof(hash), sig, sizeof(sig));
    strncat(message, sig, 4);
}