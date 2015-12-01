#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MenuLevel.h"
#include "TestLevel.h"
#include "../Random.h"
MenuLevel::MenuLevel(Game *game) : Level(game) {
    seed_ticks_ = 0;
}

void MenuLevel::render(TFT *tft) {
    const char *text = "Touch the screen to continue";
    const uint8_t title_size = 4;

    // Render the coolest title in the world (Math to center it horizontally, the 8 is because of 8 bits)
    tft->drawText((tft->lcd_width / 2) - (((float) strlen(menu_title_) / 2) * 8 * title_size), tft->lcd_height / 4,
                  menu_title_, RGB(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55), RGB(0, 0, 0), title_size);
    tft->drawText((tft->lcd_width / 2) - (((float) strlen(text) / 2) * 8), tft->lcd_height - 20, text,
                  RGB(255, 255, 255), RGB(0, 0, 0), 1);

    // Check if the screen is touched
    if (tft->touchRead()) {
        // Set new level
        game->set_level(new TestLevel(game));
    }
}

void MenuLevel::update(float deltaTime) {
    seed_ticks_++;
    Random::generate_seed(seed_ticks_ , game->nunchuck);
}