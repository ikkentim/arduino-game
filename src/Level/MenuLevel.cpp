#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MenuLevel.h"
#include "TestLevel.h"
#include "../Random.h"
MenuLevel::MenuLevel(Game *game) : Level(game) {
    seed_ticks_ = 0;
}

void MenuLevel::render() {
    const char *text = "Touch the screen to continue";
    const uint8_t title_size = 4;

    float left, top;
    Color randColor, black, white;

    randColor = RGB(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
    black = RGB(0, 0, 0);
    white = RGB(255, 255, 255);

    left = (game->tft->lcd_width / 2) - (((float) strlen(menu_title_) / 2) * 8 * title_size);
    top = game->tft->lcd_height / 4;
    // Render the coolest title in the world (Math to center it horizontally, the 8 is because of 8 bits)
    game->tft->drawText(left, top, menu_title_, randColor, black, title_size);

    left = (game->tft->lcd_width / 2) - (((float) strlen(text) / 2) * 8);
    top = game->tft->lcd_height - 20;
    game->tft->drawText(left, top, text, white, black, 1);
}

void MenuLevel::update(float deltaTime) {
    // Check if the screen is touched
    if (game->tft->touchRead()) {
        // Set new level
        game->set_level(new TestLevel(game));
    }

    seed_ticks_++;
    Random::generate_seed(seed_ticks_ , game->nunchuck);
}