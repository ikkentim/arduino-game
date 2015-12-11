#include "Bullet.h"
#include "../FastMath.h"
#include <avr/pgmspace.h>
#include "Player.h"

const int8_t bulletShape[] PROGMEM = {
        0, 1, 0, 0
};

Bullet::Bullet(Game *game, TestLevel *level, Player *player) : BaseEntity(game, level) {
    collision_radius = 1;
    rotation = player->rotation;
    // Calculate velocity depending on player rotation and velocity
    velocity.x = fast_cos(rotation) * (player->velocity.x + default_velocity);
    velocity.y = fast_sin(rotation) * (player->velocity.y + default_velocity);
    position.x = player->position.x + fast_cos(rotation) * 17;
    position.y = player->position.y + fast_sin(rotation) * 17;
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
