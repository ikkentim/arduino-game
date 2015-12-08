#include <avr/pgmspace.h>
#include "Bullet.h"
#include "Player.h"
#include "../FastMath.h"

const int8_t bulletShape[] PROGMEM = {
        0,2
};

Bullet::Bullet(Game *game, Player *player) : BaseEntity(game) {
    // Set base values for the bullet, depending on player position/speed/rotation
    velocity.x = (player->velocity.x + defaultVelocity);
    velocity.y = (player->velocity.y + defaultVelocity);
    rotation = player->rotation;

    // Set position + offset so bullet fires from the tip
    position = player->position;
    position.x += fast_cos(rotation) * 17;
    position.y += fast_sin(rotation) * 17;
}

void Bullet::render() {

}

void Bullet::update(float delta) {
   position = position + velocity * delta;
}