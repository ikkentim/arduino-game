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

    game_->sr.render(game_->tft, (int8_t *) bulletShape, 1, RGB(255, 255, 255), old_position_x,
                    old_position_y, rotation, (int) draw_position.x, (int) draw_position.y, rotation);


	old_position_x = draw_position.x;
	old_position_y = draw_position.y;
}

void Bullet::update(const float& delta) {
    position = position + velocity * delta;

    // Check if bullet exits viewport, if so, remove the bullet
    if (!level_->viewport.is_in_range(position, 20))
    {
        level_->removeEntity(this);
    }
}

void Bullet::collided(BaseEntity *other) {

}
