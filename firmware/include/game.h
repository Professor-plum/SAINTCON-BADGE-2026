#ifndef GAME_H
#define GAME_H

#include "hexutils.h"
#include "eventbase.h"
#include "bsp/common.h"

#define CREW_SPECIALTY_PILOT 0
#define CREW_SPECIALTY_ENGINEER 1
#define CREW_SPECIALTY_SCIENTIST 2
#define CREW_SPECIALTY_SOLDIER 3
#define CREW_SPECIALTY_MEDIC 4

typedef struct {
    int seed;
    int poi_market_rate[10];
    Hex poi[10];
    Hex nebula;
    Hex astroids[6];
    Hex player;
    int heading;
    int hull;
    int fuel;
    int credits;
    int cargo;
    int reputation;
    int xp;
} game_state_t;

typedef struct {
    int xp;
    game_character_t self;
    uint32_t achievments; // Bitfield for achievments
} persistant_state_t;

typedef struct {
    int max_fuel;
    int max_hull;
    int max_cargo;
} game_config_t;

enum tiletype {
    TILE_EMPTY,
    TILE_NEBULA,
    TILE_ASTROID,
    TILE_HOME,
    TILE_POI
};

void game_run();

#endif // GAME_H