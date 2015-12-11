#include "Level.h"

Level::Level(Game* game) {
    this->game = game;

    for(int i = 0; i < MAX_ENTITY_COUNT; i++) {
        entities[i] = 0;
    }
}

Level::~Level() {

}

void Level::update(float delta) {

}

void Level::addEntity(BaseEntity *entity) {
    if(entityCount < MAX_ENTITY_COUNT){
        entities[entityCount++] = entity;
    }
}

void Level::removeEntity(BaseEntity *entity) {
    for(int i = 0; i < entityCount; i++) {
        if (entities[i] == entity) {
            entities[i] = entities[--entityCount];
            // Remove the entity
            delete entity;
            entity = 0;

            return;
        }
    }
}
