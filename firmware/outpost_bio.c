#include "outposts.h"
#include "bsp/framebuffer.h"
#include "bsp/buttons.h"
#include "img/outpost_bio.h"



void outpost_bio_run() {
    frame_draw_image(0, 0, outpost_bio_image_data, 360, 360);
    frame_refresh();
    buttons_clear(); // Clear any button presses that happened during the text display
    while (!(buttons_get_and_clear() & BUTTON_PRESS)) {
        sleep_ms(10);
        // Wait for button press to exit console UI
    }
}