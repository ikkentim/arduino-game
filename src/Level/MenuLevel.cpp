#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <EEPROM.h>
#include "MenuLevel.h"
#include "TestLevel.h"
#include "../Random.h"
#include "../Color.h"
#include "../Game.h"
#include "GameOver.h"
#include "../Highscore.h"

MenuLevel::MenuLevel(Game *game) : Level(game) {
    seed_ticks_ = 0;
    game->score->set_score(0);
}

void MenuLevel::render() {
    const uint8_t title_size = 4;

    float left, top;
    Color randColor, black;

    randColor = RGB(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);

    left = (game->tft->width / 2) - (((float) strlen(menu_title_) / 2) * 8 * title_size);
    top = game->tft->height / 4;
    // Render the coolest title in the world (Math to center it horizontally, the 8 is because of 8 bits)
    game->tft->draw_text(left, top, menu_title_, randColor, black, title_size);

}

void MenuLevel::update(float delta) {
    // Check if the screen is touched
    if (game->tft->touch_read() || game->nunchuck->button_z()) {
        // Set new level
        game->set_level(new TestLevel(game));
    }

    seed_ticks_++;
    Random::generate_seed(seed_ticks_ , game->nunchuck);
}

void MenuLevel::pre_render() {
    const char *text = "Touch the screen to continue";
    float left, top;
    Color white, black;
    black = RGB(0, 0, 0);
    white = RGB(255, 255, 255);

    left = (game->tft->width / 2) - (((float) strlen(text) / 2) * 8);
    top = game->tft->height - 20;
    game->tft->draw_text(left, top, text, white, black, 1);

    Highscore highscore;
    EEPROM.begin();
    EEPROM.get(0, highscore);
    EEPROM.end();

    if(highscore.is_valid()) {
        char buf[16];
        sprintf(buf, "%s: %d", highscore.name, highscore.score);

        game->tft->draw_text(left, top-30, buf, white, black, 1);
    }
}
