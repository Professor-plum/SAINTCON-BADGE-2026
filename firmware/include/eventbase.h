
#include <stdint.h>

#define EV_EFFECT_HULL 0
#define EV_EFFECT_FUEL 1
#define EV_EFFECT_CREDITS 2
#define EV_EFFECT_CREW 3
#define EV_EFFECT_CARGO 4
#define EV_EFFECT_REPUTATION 5
#define EV_EFFECT_XP 6

#define EV_FLAG_REQUIRES_PILOT 1
#define EV_FLAG_REQUIRES_ENGINEER 2
#define EV_FLAG_REQUIRES_SCIENTIST 4
#define EV_FLAG_REQUIRES_SOLDIER 8
#define EV_FLAG_REQUIRES_MEDIC 16
#define EV_FLAG_REQUIRES_CARGO 32
#define EV_FLAG_REQUIRES_CREDITS 64
#define EV_FLAG_REQUIRES_FUEL 128

typedef struct event_effect {
    uint8_t type;
    int16_t value;
} event_effect_t;

typedef struct event_outcome {
    const char* description;
    const char* name;
    uint8_t chance;
    uint8_t effect_count;
    event_effect_t effects[4]; // Up to 4 effects per outcome
} event_outcome_t;

typedef struct event_option {
    const char* description;
    uint8_t requirements;
    uint8_t required_count;
    uint8_t outcome_count;
    event_outcome_t outcomes[4]; // Up to 4 outcomes per event
} event_option_t;

typedef struct event {
    uint8_t id;
    const char* title;
    const char* description;
    uint8_t option_count;
    event_option_t options[4]; // Up to 4 options per event
} event_t;