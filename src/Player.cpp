#include "Player.h"
#include <avr/pgmspace.h>
#include "FastMath.h"

const int8_t playerShape[] PROGMEM = {
        -5, 6, 0, 0,
        -5, -6, 0, 0,
        -5, 6, 15, 0,
        -5, -6, 15, 0
};

Player::Player(Game *game) : BaseEntity(game) {
    position = Vector2(50, 50);

    collision_check = true;
    collision_radius = 16;

    dead_ = false;
}

void Player::update(float delta) {

    if (game_->nunchuck->button_z() && !dead_) {
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
    if(!dead_){
        rotation += game_->nunchuck->joystick().x * rotation_speed_ * delta;
    }

    position = position + velocity * delta;
}

void Player::render() {
    game_->sr.render(game_->tft, (int8_t *) playerShape, 4, RGB(255, 255, 255), (int) old_position.x,
                     (int) old_position.y, old_rotation, (int) position.x, (int) position.y, rotation);

    old_rotation = rotation;
    old_position = position;
}

void Player::collided(BaseEntity *other) {
    dead_ = true;
}
