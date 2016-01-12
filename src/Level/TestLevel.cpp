#include <stdio.h>
#include "TestLevel.h"
#include "../Entity/Asteroid.h"
#include "../Entity/Player.h"
#include "../Entity/PowerUp.h"
#define VIEWPORT_PADDING    100
#define MAX_ASTEROID_COUNT  3

TestLevel::TestLevel(Game *game) : Level(game) {
    viewport = Viewport(0, 0, game->tft->width, game->tft->height);

    player_ = new Player(game, this);

    addEntity(player_);
    //Powerup position set by Asteroid reset
    PowerUp* pupp = new PowerUp(game, this);
    addEntity(pupp);

    for (int i = 0; i < MAX_ASTEROID_COUNT; i++)
    {
        //Asteroid sets its own position
        addEntity(new Asteroid(game, this, pupp));
    }

}

TestLevel::~TestLevel() {
}

void TestLevel::update(float delta) {
    for( int i = 0; i < entityCount; i++){
        entities[i]->update(delta);
    }
    update_viewport();

    time_since_score_ -= delta;
}

void TestLevel::render() {
    for( int i = 0; i < entityCount; i++){
        entities[i]->render();
    }

    if(game->score->has_changed() || time_since_score_ <= 0) {
        char buf[32];
        sprintf(buf, "Score: %d", game->score->get_score());

        game->tft->draw_text(5, 225, buf, RGB(255, 255, 255), RGB(0, 0, 0), 1);
        time_since_score_ = 1.0f;
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

void TestLevel::pre_render() {

}
