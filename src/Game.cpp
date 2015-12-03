#include "Game.h"
#include "Level/TestLevel.h"
#include "Level/MenuLevel.h"

Game::Game(Nunchuck *nunchuck, TFT *tft) : Engine(nunchuck, tft) {
    this->level = new MenuLevel(this);
}

void Game::engine_update(float deltaTime) {
    nunchuck->update();

    if(this->level != 0){
        this->level->update(deltaTime);
    }
}

void Game::engine_render() {
    if(this->level != 0) {
        this->level->render();
    }
}

void Game::set_level(Level *level) {
    if (this->level != 0) {
        delete this->level;
        this->level = 0;
    }
    tft->fillScreen(0x00);
    this->level = level;
}
