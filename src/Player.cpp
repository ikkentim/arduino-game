#include "Player.h"

Player::Player(Game *game) : BaseEntity(game) {

}

void Player::update(float delta) {
    position += game_->nunchuck->joystick() * move_speed_ * delta;
}

void Player::render(ShapeRenderer *renderer) {

}

