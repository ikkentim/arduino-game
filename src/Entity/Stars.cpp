#include "Stars.h"
#include "../Random.h"
#include "Player.h"
#include "../Level/Level.h"
#include <math.h>

Stars::Stars(Game *game, TestLevel *level, Player *player) : BaseEntity(game, level) {
    player_ = player;
    // Fill the initial background with stars
    for (int i = 0; i < MAX_STAR_COUNT; i++)
    {
        // Add a new star and immediately reset it
        Star* star = new Star();
        star->brightness = rand_uint8_t(50, 155);
        // Generate initial position within viewport
        star->position = Vector2(
                rand_float(level->viewport.position().x, level->viewport.size().x),
                rand_float(level->viewport.position().y, level->viewport.size().y));
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
        star->offset += 50;

        // Calculate how far stars have to move in the next render call, opposite of the player velocity/4 for parallax
        stars_position_offset_ = (player_->velocity * -1 * 0.8) * delta;

        // Check if stars are off screen
        if (!level_->viewport.is_in_range(level_->viewport.position() + star->position, 30)) {
            reset_star(star);
        }
    }
}

void Stars::render() {
    for (int i = 0; i < MAX_STAR_COUNT; i++) {
        Star* star = stars_[i];
        // Roelof's mathemagic
        uint8_t brightness = star->brightness + abs((float) star->offset) / 127.f * MAX_OFFSET;

        // Calculate new position since last updates.
        Vector2 last_position = star->position;
        star->position = star->position + stars_position_offset_;

        // Undraw if position has changed
        if (star->position != last_position) {
            game_->tft->draw_pixel(last_position.x, last_position.y, 0);
        }

        game_->tft->draw_pixel(star->position.x, star->position.y, RGB(brightness, brightness, brightness));
    }
}

void Stars::reset_star(Star *star) {
    // undraw the old star
    game_->tft->draw_pixel(star->position.x, star->position.y, 0);
    uint8_t brightness = rand_uint8_t(75, 155);

    Vector2 viewport_position = level_->viewport.position();
    Vector2 viewport_size = level_->viewport.size();

    // Generate position in the direction the player is going
    Vector2 position = player_->position - (viewport_position + viewport_size /2);
    position.normalize();
    position.x += rand_float(-1, 1);
    position.y += rand_float(-1, 1);
    position.normalize();
    position = (viewport_position + viewport_size / 2) + position * viewport_size.length() / 2 - viewport_position;

    star->brightness = brightness;
    star->position = position;
}



