#include "Game.h"
#include "Level/TestLevel.h"
#include "Level/MenuLevel.h"

Game::Game(Nunchuck *nunchuck, TFT *tft) : Engine(nunchuck, tft) {
    this->level = new MenuLevel(this);
}

void Game::engine_update(float deltaTime) {
    nunchuck->update();

    if (this->level != 0) {
        this->level->update(deltaTime);
    }
}

void Game::collision_detection() {
    for(int i = 0; i < MAX_ENTITY_COUNT; i++){
        BaseEntity* entity = this->level->entities[i];

        if(entity != 0 && entity->collision_check) {
            for (int j = 0; j < MAX_ENTITY_COUNT; ++j) {
                BaseEntity* entity2 = this->level->entities[j];

                if(entity != entity2){
                    if((entity->position - entity2->position).length() < 32) {
                        tft->fillScreen(RGB(255, 0, 0));
                    }
                }
            }
        }
    }
}

void Game::engine_render() {
    if (this->level != 0) {
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
