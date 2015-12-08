#include "Player.h"
#include <avr/pgmspace.h>
#include "../Level/TestLevel.h"
#include "../FastMath.h"

const int8_t playerShape[] PROGMEM = {
        -5, 6, 0, 0,
        -5, -6, 0, 0,
        -5, 6, 15, 0,
        -5, -6, 15, 0
};

Player::Player(Game *game, TestLevel *level) : BaseEntity(game, level) {
    position = Vector2(50, 50);
}

void Player::update(float delta) {

    if (game_->nunchuck->button_z()) {
        // add relative velocity so you get a drag effect
        velocity.y += fast_sin(rotation) * acceleration_ * delta;
        velocity.x += fast_cos(rotation) * acceleration_ * delta;
    } else {
        velocity += -velocity * deceleration_ * delta;
    }

    // if speed is faster than max speed, clamp it
    if (velocity.length_sq() > square(max_speed_)) {
        velocity = velocity.normalized() * max_speed_;
    }

    // add rotations
    rotation += game_->nunchuck->joystick().x * rotation_speed_ * delta;

    position = position + velocity * delta;
}

void Player::render() {
    Vector2 draw_position = position - level_->viewport.position();

    game_->sr.render(game_->tft, (int8_t *) playerShape, 4, RGB(255, 255, 255), (int) (old_position.x),
                     (int) old_position.y, old_rotation, (int) draw_position.x, (int) draw_position.y, rotation);

    old_rotation = rotation;
    old_position = draw_position;
}

