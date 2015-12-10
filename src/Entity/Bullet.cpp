#include <avr/pgmspace.h>
#include "Bullet.h"
#include "Player.h"
#include "../FastMath.h"

const int8_t bulletShape[] PROGMEM = {
    0, 2, 0, 0
};

Bullet::Bullet(Game *game, Player *player, TestLevel *level) : BaseEntity(game, level) {
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
    Vector2 draw_position = position - level_->viewport.position();

    game_->sr.render(game_->tft, (int8_t *) bulletShape, 1, RGB(255, 255, 255), (int) (old_position.x),
                     (int) old_position.y, rotation, (int) draw_position.x, (int) draw_position.y, rotation);

    old_position = draw_position;
}

void Bullet::update(float delta) {
    position = position + velocity * delta;
}

void Bullet::collided(BaseEntity *other) {

}