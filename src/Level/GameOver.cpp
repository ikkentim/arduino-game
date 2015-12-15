#include <stdlib.h>
#include <string.h>
#include "GameOver.h"
#include "../Color.h"
#include "../Game.h"
#include "MenuLevel.h"

void GameOver::update(float delta) {
    // Check if the screen is touched
    if (game->tft->touchRead()) {
        // Set new level
        game->set_level(new MenuLevel(game));
    }
}

void GameOver::render() {

}

void GameOver::pre_render() {
    const char *text = "Game Over";
    const uint8_t title_size = 4;

    float left, top;
    Color randColor, black, white;

    randColor = RGB(255, rand() % 150, rand() % 150);
    black = RGB(0, 0, 0);
    white = RGB(255, 255, 255);

    left = (game->tft->lcd_width / 2) - (((float) strlen(text) / 2) * 8 * title_size);
    top = game->tft->lcd_height / 6;
    // Render the coolest title in the world (Math to center it horizontally, the 8 is because of 8 bits)
    game->tft->drawText(left, top, text, randColor, black, title_size);

    char buf[32];
    sprintf(buf, "Your score: %d", game->score->get_score());


    left = (game->tft->lcd_width / 2) - (((float) strlen(buf) / 2) * 8);
    top = game->tft->lcd_height / 2;
    game->tft->drawText(left, top, buf, white, black, 1);
}

GameOver::GameOver(Game *game) : Level(game) {

}
