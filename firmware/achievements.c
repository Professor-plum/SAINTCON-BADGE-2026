#include "achievements.h"
#include "framebuffer.h"
#include "buttons.h"
#include "bsp/config.h"
#include <stdio.h>

void achievements_display() {
    buttons_clear();
    uint32_t achievments = config_get_achievements();
    int count = config_get_achievement_count();
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Achievements Unlocked: %d/32", count);
    frame_clear();
    frame_draw_text(buffer, RGB565(255, 255, 0), 30); // Yellow color
    for (int i=0; i<32; ++i) {
        if (achievments & (1<<i)) {
            char* name = config_get_achievement_name(i);
            frame_draw_text(name, RGB565(150, 150, 150), 70 + i * 20); // Gray color
        }
    }
    frame_refresh();
    while(buttons_get_raw()) {
        sleep_ms(10);
        // Wait for all buttons to be released before allowing exit
    }
    buttons_clear(); // Clear any button presses that happened during the text display
    while (!(buttons_get_and_clear() & BUTTON_PRESS)) {
        sleep_ms(10);
        // Wait for button press to exit achievements screen
    }
}