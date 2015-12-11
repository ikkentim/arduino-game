#include <stdio.h>
#include "TestLevel.h"
#include "../Entity/Asteroid.h"
#include "../Entity/Player.h"

#define VIEWPORT_PADDING    50
const uint8_t TestLevel::MAX_ASTEROID_COUNT = 5;

TestLevel::TestLevel(Game *game) :
    Level(game),
    viewport(Viewport(0, 0, game->tft->lcd_width, game->tft->lcd_height)) {
    player_ = new Player(game, this);

    addEntity(player_);
    for (int i = 0; i < MAX_ASTEROID_COUNT; i++)
    {
        //Asteroid sets its own position
        addEntity(new Asteroid(game, this));
    }
}

TestLevel::~TestLevel() {
}

void TestLevel::update(float delta) {
    for( int i = 0; i < entityCount; i++){
        entities[i]->update(delta);
    }
    update_viewport();
}

void TestLevel::render() {
    for( int i = 0; i < entityCount; i++){
        entities[i]->render();
    }
}

void TestLevel::update_viewport() {
    float left = player_->position.x - viewport.x;
    float right = viewport.x + viewport.width - player_->position.x;

    float top = player_->position.y - viewport.y;
    float bottom = viewport.y + viewport.height - player_->position.y;

    if(left < VIEWPORT_PADDING)
        viewport.x -= (VIEWPORT_PADDING - left);
    if(right < VIEWPORT_PADDING)
        viewport.x += (VIEWPORT_PADDING - right);
    if(top < VIEWPORT_PADDING)
        viewport.y -= (VIEWPORT_PADDING - top);
    if(bottom < VIEWPORT_PADDING)
        viewport.y += (VIEWPORT_PADDING - bottom);
}
