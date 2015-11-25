#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MenuLevel.h"

MenuLevel::MenuLevel(Game *game) : Level(game) {

}

void MenuLevel::render(MI0283QT9 *tft) {
    const uint8_t title_size = 4;

    // Render the coolest title in the world (Math to center it horizontally, the 8 is because of 8 bits)
    tft->drawText((tft->lcd_width / 2) - (((float) strlen(menu_title_) / 2) * 8 * title_size), tft->lcd_height / 4,
                  menu_title_, RGB(rand() % 255, rand() % 255, rand() % 255), RGB(0, 0, 0), title_size);

}

void MenuLevel::update() {

}