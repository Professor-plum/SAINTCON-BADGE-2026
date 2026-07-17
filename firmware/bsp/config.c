#include "config.h"
#include "bsp_komihash.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "ws2812.h"
#include "pico/unique_id.h"
#include "pico/rand.h"
#include "eeprom.h"
#include "base64.h"
#define KOMISEED    0x50726f66506c756d

typedef struct _config_t {
    char handle[15];
    char class;
    uint32_t achievements;
    uint16_t totalscore;
    uint16_t unused;
    uint64_t hash;
} config_t;

config_t g_config={0};
uint16_t pending_score = 0;
char* achieve_str = NULL;
char my_id[13] = {0};

uint64_t achievement_hashes[32] = {
    0,
    0,
    0xa60d149ba625229fULL, // SC_VECTOR_BURN
    0x2e0bf85ad010dbb2ULL, // SC_NOVA_TRACE
    0x4750921fb1958f66ULL, // SC_ION_WAKE
    0x666d527fb94e3da0ULL, // SC_SOLAR_SHEAR
    0x80a5aedb8684c3b4ULL, // SC_PLASMA_ARC
    0x54cd46567937ecbdULL, // SC_VOID_VECTOR
    0xc327e386d9189b63ULL, // SC_STAR_OFFSET
    0xd1ff3ce39c469e68ULL, // SC_ORBIT_DECAY
    0x3c317b15e7c1e29dULL, // SC_THRUST_LOSS        - RE flash
    0xa1d4a114f76211b7ULL, // SC_SIGNAL_GHOST       - EEPROM
    0x95c911db5174adaeULL, // SC_ECHO_ORBIT         - Hardcoded //TODO
    0x236c4a02f5b53468ULL, // SC_DUST_FLUX          - USB UART
    0xca5d48f6551e91a6ULL, // SC_PHASE_DRIFT        - USB DOCK
    0x3b21dd157c302499ULL, // SC_GRAV_SHIFT         - Crypto //TODO
    0x2b649143bd4140b1ULL, // SC_CORE_FLUX          - Boot //TODO
    0x73d4fbc7ac29b3ffULL, // SC_LAGRANGE_LOCK      - Badge Art 5 bit
    0x187b1fcf223c7378ULL, // SC_PULSE_FIELD        - Badge art Contelations
    0x1d3ba22e7f078e03ULL, // SC_FIELD_ECHO         - Committee
    0x5d0f1b55a201937eULL, // SC_QUANTUM_WAKE
    0x3260bcce868c358cULL, // SC_DEEP_PARALLAX
    0xa3ffa1442b62a8b9ULL, // SC_RADIAL_DRIFT
    0xfd4dcde6773030f5ULL, // SC_COSMIC_BIAS
    0x72b59e0887bae55cULL, // SC_FLUX_VECTOR
    0xbd21f31f1860e478ULL, // SC_ORBIT_TRACE
    0x5bb3c9f2243bcbddULL, // SC_ASTRA_SHIFT
    0x36ee9016f26b3c8dULL, // SC_ZENITH_DRIFT
    0x70dd514041fafbf3ULL, // SC_ECHO_VECTOR
    0xb377e54b5a08a833ULL, // SC_DRIFT_LOCK
    0x6c01b05f902d9e09ULL, // SC_APOGEE_DRIFT
    0xfccc75461d4f2fe2ULL, // SC_PERIGEE_SHIFT
};

char *achievement_names[32] = {
    "Thirty Lives", 
    "First Departure",
    "Frequent Flyer",
    "Echoes of the First Builders",
    "The Black Obelisk",
    "Full Complement",
    "A Crew of Specialists",
    "Signed On",
    "Works Well With Others",
    "Civic Duty",
    "Deep Storage",
    "Long-Term Memory",
    "Written in Stone",
    "Service Port",
    "Dockmaster's Channel",
    "Encrypted Transmission",
    "Diagnostics Complete",
    "Circles Within Circles",
    "Connect the Dots",
    "Know a Guy",
    "UNKNOWN",
    "UNKNOWN"
};

void config_set_id() {
    pico_unique_board_id_t id;
    pico_get_unique_board_id (&id);
    base64_encode((uint8_t*)&id, sizeof(id), my_id, sizeof(my_id));
    my_id[6] = '\0';
    printf("Board ID: %llX my_id:%s\n", *(uint64_t*)(&id), my_id);

}

int config_load() {
    config_set_id();
    memset(&g_config, 0, sizeof(g_config));
    int ret = eeprom_readbytes(CONFIG_ADDR, (uint8_t*)&g_config, sizeof(g_config));
    printf("eeprom_read returned %d\n", ret);
    printf("Config read: %s %c %d %d %d %llx\r\n",
        g_config.handle, g_config.class, g_config.achievements, g_config.totalscore,
        g_config.unused, g_config.hash);
    uint64_t hash = komihash(&g_config, sizeof(g_config)-8, KOMISEED);
    printf("%llx %c= %llx\r\n", g_config.hash, hash == g_config.hash? '=':'!', hash);
    return hash == g_config.hash;
}

void config_write() {
    g_config.hash = komihash(&g_config, sizeof(g_config)-8, KOMISEED);
    int ret = eeprom_writebytes(CONFIG_ADDR, (uint8_t*)&g_config, sizeof(g_config));
    printf("eeprom_write returned %d\n", ret);
}

void config_clear() {
    memset(&g_config, 0, sizeof(g_config));
    g_config.class = 'A' + (get_rand_32() %5);
    config_generate_handle();
    config_write();
    char eeprom_unlock[] = {6, 22, 10, 6, 28, 18, 27, 20, 25, 10, 18, 29, 26, 6, 1, 0x55}; //SC_SIGNAL_GHOST
    for (int i=0; i< 16; ++i)
        eeprom_unlock[i]^= 0x55;
    eeprom_writebytes(0, eeprom_unlock, sizeof(eeprom_unlock));
    printf("Config writen: %s %c %d %d %d %llx\r\n",
         g_config.handle, g_config.class, g_config.achievements, g_config.totalscore,
        g_config.unused, g_config.hash);
}

void config_set_handle(const char* name) {
    strncpy(g_config.handle, name, 15);
    config_write();
}

void config_redeem_score() {
    g_config.totalscore += pending_score;
    if (g_config.totalscore > 5000) {
        config_achievement(game_quota);
    }
    pending_score = 0;
    config_write();
}

int config_get_score() {
    return g_config.totalscore;
}

int config_get_achievement_count() {
    int count = 0;
    for (int i=0; i<32; ++i) {
        if (g_config.achievements & (1<<i)) {
            count++;
        }
    }
    return count;
}

uint32_t config_get_achievements() {
    return g_config.achievements;
}

char* config_get_handle() {
    return g_config.handle;
}

char config_get_class() {
    return g_config.class;
}

char* config_get_class_name() {
    switch (g_config.class) {
        case 'A': return "Pilot";
        case 'B': return "Engineer";
        case 'C': return "Scientist";
        case 'D': return "Soldier";
        case 'E': return "Medic";
        default: return "Unknown";
    }
}

static const char* pilot_name_pool_1[50] = {
    "Aerion", "Blaze", "Cypher", "Drake", "Eclipt", "Falco", "Galaxy", "Hawke",
    "Ignite", "Jetson", "Krypta", "Lunar", "Matrix", "Nexus", "Oracle", "Pulsar",
    "Quasar", "Ranger", "Sirius", "Titan", "Unison", "Vector", "Warped", "Xenith",
    "Yonder", "Zealot", "Astra", "Brave", "Corvus", "Deltar", "Elixir", "Forge",
    "Gravus", "Helion", "Inert", "Junoxy", "Kalibr", "Lumina", "Mirage", "Noctis",
    "Origen", "Photon", "Quinox", "Rey", "Stell", "Talion", "Usher", "Vortex",
    "Wraith", "Xycor"
};

static const char* pilot_name_pool_2[50] = {
    "Arion", "Bolter", "Citro", "Dexter", "Ensign", "Fusion", "Gambit", "Horiz",
    "Inert", "Javel", "Kernel", "Legion", "Mantis", "Nimbus", "Omnia", "Phonyx",
    "Quanta", "Raptor", "Scion", "Talon", "Uplink", "Vulcan", "Widgit", "Xyste",
    "Yale", "Zenith", "Arcade", "Binary", "Cirrus", "Dynamo", "Echo", "Flux",
    "Grado", "Hunter", "Illume", "Joule", "Kalmix", "Lance", "Novia", "Orbit",
    "Pandor", "Quorum", "Radius", "Strata", "Torque", "Umbrae", "Vigor", "Welkin",
    "Xeno", "Zepra"
};

void config_generate_handle(void) {
    const char* first = pilot_name_pool_1[get_rand_32() % 50];
    const char* second = pilot_name_pool_2[get_rand_32() % 50];
    
    memset(g_config.handle, 0, sizeof(g_config.handle));
    snprintf(g_config.handle, sizeof(g_config.handle), "%s %s", first, second);
}

int config_submit(const char* key) {
    uint64_t hash = komihash(key, strlen(key), KOMISEED);
    for (int i=0; i<32; ++i) {
        if (hash == achievement_hashes[i]) {
            return config_achievement(i);
        }
    }
    ws2812_show_alert((ws2812_rgb_t){32,0,0});
    return -1;
}

int config_achievement(enum achievement id) {
    if (g_config.achievements & (1<<id)) {
        return 0;
    }
    else {
        g_config.achievements |= (1<<id);
        config_write();
        achieve_str = achievement_names[id];
        ws2812_show_alert((ws2812_rgb_t){32,0,32});
        return 1;
    }
}

char* config_get_achievement_name(enum achievement id) {
    if (id < 0 || id >= 32) return "Invalid Achievement";
    return achievement_names[id];
}

char* config_get_id() { 
    return my_id;
}