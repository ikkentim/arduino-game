#include "Stars.h"
#include "../Random.h"
#include <math.h>

Stars::Stars(Game *game, TestLevel *level) : BaseEntity(game, level) {
    // Fill the initial background with stars
    for (int i = 0; i < MAX_STAR_COUNT; i++)
    {
        // Add a new star and immediately reset it
        Star* star = new Star();
        reset_star(star);
        stars_[i] = star;
    }
}

Stars::~Stars() {
    for (int i = 0; i < MAX_STAR_COUNT; i++) {
        delete stars_[i];
    }
}

void Stars::update(const float &delta) {
    for (int i = 0; i < MAX_STAR_COUNT; i++) {
        Star* star = stars_[i];
        star->offset+=50;

        // Move stars

        // Check if stars are off screen
        // Reset star
    }
}

void Stars::render() {
    for (int i = 0; i < MAX_STAR_COUNT; i++) {
        Star* star = stars_[i];
        // Magic
        uint8_t brightness = star->brightness + abs((float) star->offset) / 127.f * MAX_OFFSET;

        game_->tft->draw_pixel(star->x, star->y, RGB(brightness, brightness, brightness));
    }
}

void Stars::reset_star(Star *star) {
    uint8_t type = rand_uint8_t(0, 2); // determines the star color
    uint8_t brightness = rand_uint8_t(50, 155);

    float x = rand_float(0, game_->tft->width);
    float y = rand_float(0, game_->tft->height);

    star->type = type;
    star->brightness = brightness;
    star->x = x;
    star->y = y;
}

void Stars::collided(BaseEntity *other) {

}



