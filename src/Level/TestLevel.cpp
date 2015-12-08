#include <stdio.h>
#include "TestLevel.h"
#include "../Entity/TestEntity.h"
#include "../Entity/Asteroid.h"

#define VIEWPORT_PADDING    50

TestLevel::TestLevel(Game *game) :
    Level(game),
    viewport(Viewport(0, 0, game->tft->lcd_width, game->tft->lcd_height)) {
    player_ = new Player(game, this);
    testAsteroid_ = new Asteroid(game, this);
}

TestLevel::~TestLevel() {
}

void TestLevel::update(float deltaTime) {
    player_->update(deltaTime);
    testAsteroid_->update(deltaTime);

    update_viewport();
}

void TestLevel::render() {
    player_->render();
    testAsteroid_->render();
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
