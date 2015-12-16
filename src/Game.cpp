#include <stdio.h>
#include "Game.h"
#include "Level/TestLevel.h"
#include "Level/MenuLevel.h"
#include "Entity/BaseEntity.h"
#include "Level/GameOver.h"

Game::Game(Nunchuck *nunchuck, TFT *tft) : Engine(nunchuck, tft) {
    this->level = 0;
    this->score = new Score;
    set_level(new MenuLevel(this));
}

void Game::engine_update(float deltaTime) {
    nunchuck->update();

    if (this->level != 0) {
        this->level->update(deltaTime);
    }
}

void Game::collision_detection() {
    for(int i = 0; i < this->level->entityCount; i++){
        BaseEntity* entity = this->level->entities[i];

        if(entity->collision_check) {
            for (int j = 0; j < this->level->entityCount; ++j) {
                BaseEntity* entity2 = this->level->entities[j];

                if(entity != entity2) {
                    if((entity->position - entity2->position).length() < entity->collision_radius + entity2->collision_radius) {
                        entity->collided(entity2);
                        break;
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

    this->level->pre_render();
}
