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
}

void Player::update(float delta) {
    old_rotation = rotation;
    old_position = position;

    move_speed_ += game_->nunchuck->joystick().y * acceleration_ * delta;
    rotation += game_->nunchuck->joystick().x * rotation_speed_ * delta;

    velocity = Vector2(fast_cos(rotation), fast_sin(rotation)).normalized();

    position = position + velocity * move_speed_;
}

void Player::render()
{
    game_->sr.render(game_->tft, (int8_t *)playerShape, 4, RGB(255,255,255), (int)old_position.x, (int)old_position.y, old_rotation, (int)position.x, (int)position.y, rotation);
}

