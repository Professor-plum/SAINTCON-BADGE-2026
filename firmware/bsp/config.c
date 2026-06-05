#include "config.h"
#include "bsp_komihash.h"
#include <stdint.h>
#include <string.h>
#include "ws2812.h"

#define KOMISEED    0x50726f66506c756d

typedef struct _config_t {
    char handle[11];
    char class;
    uint32_t unlocks;
    uint16_t totalscore;
    uint16_t unused;
    uint64_t hash;
} config_t;

config_t g_config={0};
uint16_t pending_score = 0;

uint64_t unlock_hashes[30] = {
    0x6c01b05f902d9e09ULL, // SC_APOGEE_DRIFT
    0xfccc75461d4f2fe2ULL, // SC_PERIGEE_SHIFT
    0x73d4fbc7ac29b3ffULL, // SC_LAGRANGE_LOCK      - Badge Art 5 bit
    0x4750921fb1958f66ULL, // SC_ION_WAKE
    0x666d527fb94e3da0ULL, // SC_SOLAR_SHEAR
    0x80a5aedb8684c3b4ULL, // SC_PLASMA_ARC
    0x54cd46567937ecbdULL, // SC_VOID_VECTOR
    0xc327e386d9189b63ULL, // SC_STAR_OFFSET
    0xd1ff3ce39c469e68ULL, // SC_ORBIT_DECAY
    0x236c4a02f5b53468ULL, // SC_DUST_FLUX          - USB UART
    0x95c911db5174adaeULL, // SC_ECHO_ORBIT
    0xca5d48f6551e91a6ULL, // SC_PHASE_DRIFT
    0x3b21dd157c302499ULL, // SC_GRAV_SHIFT
    0x2b649143bd4140b1ULL, // SC_CORE_FLUX
    0xa60d149ba625229fULL, // SC_VECTOR_BURN
    0x2e0bf85ad010dbb2ULL, // SC_NOVA_TRACE
    0x1d3ba22e7f078e03ULL, // SC_FIELD_ECHO
    0x5d0f1b55a201937eULL, // SC_QUANTUM_WAKE
    0x3260bcce868c358cULL, // SC_DEEP_PARALLAX
    0xa3ffa1442b62a8b9ULL, // SC_RADIAL_DRIFT
    0xfd4dcde6773030f5ULL, // SC_COSMIC_BIAS
    0x3c317b15e7c1e29dULL, // SC_THRUST_LOSS        - RE flash
    0xa1d4a114f76211b7ULL, // SC_SIGNAL_GHOST       - RE medium
    0x72b59e0887bae55cULL, // SC_FLUX_VECTOR
    0xbd21f31f1860e478ULL, // SC_ORBIT_TRACE
    0x5bb3c9f2243bcbddULL, // SC_ASTRA_SHIFT
    0x36ee9016f26b3c8dULL, // SC_ZENITH_DRIFT
    0x187b1fcf223c7378ULL, // SC_PULSE_FIELD        - Badge art Contelations
    0x70dd514041fafbf3ULL, // SC_ECHO_VECTOR
    0xb377e54b5a08a833ULL, // SC_DRIFT_LOCK
};

int config_load() {

}

void config_write() {
    g_config.hash = komihash(&g_config, sizeof(g_config)-8, KOMISEED);

}

void config_clear() {
    memset(&g_config, 0, sizeof(g_config));
    config_write();
}

void config_set_handle(const char* name) {
    strncpy(g_config.handle, name, 10);
    config_write();
}

void config_redeem_score() {
    g_config.totalscore += pending_score;
    if (g_config.totalscore > 5000) {
        config_unlock(game_quota);
    }
    pending_score = 0;
    config_write();
}

int config_get_score() {
    return g_config.totalscore;
}

int config_get_unlock_count() {
    int count = 0;
    for (int i=0; i<32; ++i) {
        if (g_config.unlocks & (1<<i)) {
            count++;
        }
    }
    return count;
}

uint32_t config_get_unlocks() {
    return g_config.unlocks;
}

char* config_get_handle() {
    return g_config.handle;
}

char config_get_class() {
    return g_config.class;
}

int config_submit(const char* key) {
    uint64_t hash = komihash(key, strlen(key), KOMISEED);
    for (int i=0; i<30; ++i) {
        if (hash == unlock_hashes[i]) {
            return config_unlock(i);
        }
    }
    ws2812_show_alert((ws2812_rgb_t){32,0,0});
    return -1;
}

int config_unlock(enum unlock id) {
    if (g_config.unlocks & (1<<id)) {
        ws2812_show_alert((ws2812_rgb_t){32,32,0});
        return 0;
    }
    else {
        g_config.unlocks |= (1<<id);
        config_write();
        ws2812_show_alert((ws2812_rgb_t){0,32,0});
        return 1;
    }
}

