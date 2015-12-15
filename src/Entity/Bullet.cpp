#include "Bullet.h"
#include "../FastMath.h"
#include <avr/pgmspace.h>
#include "Player.h"
#include "Asteroid.h"

const int8_t bulletShape[] PROGMEM = {
        0, 2, 0, 0
};

Bullet::Bullet(Game *game, TestLevel *level, Player *player) : BaseEntity(game, level) {
    entity_type = TYPE_BULLET;

    collision_check = true;
    collision_radius = 1;
    rotation = player->rotation;
    // Calculate velocity depending on player rotation and velocity
    velocity.x = fast_cos(rotation) * default_velocity + player->velocity.x;
    velocity.y = fast_sin(rotation) * default_velocity + player->velocity.y;
    position.x = player->position.x + fast_cos(rotation) * 25;
    position.y = player->position.y + fast_sin(rotation) * 25;
}

void Bullet::render() {
    Vector2 draw_position = position - level_->viewport.position();

    game_->sr.render(game_->tft, (int8_t *) bulletShape, 1, RGB(255, 120, 0), (int) (old_position.x),
                     (int) old_position.y, rotation, (int) draw_position.x, (int) draw_position.y, rotation);

    old_position = draw_position;
}

void Bullet::update(float delta) {
    static int count = 0;

    position = position + velocity * delta;

    // Check if bullet exits viewport, if so, remove the bullet
    if (!level_->viewport.is_in_range(position, 30))
    {
        count++;
        level_->removeEntity(this);
    }
}

void Bullet::collided(BaseEntity *other) {
    if (other->entity_type == TYPE_ASTEROID) {
        ((Asteroid*) other)->reset();

        Vector2 draw_position = position - level_->viewport.position();
        game_->sr.render(game_->tft, (int8_t *) bulletShape, 1, RGB(0, 0, 0), (int) (old_position.x),
                         (int) old_position.y, rotation, (int) draw_position.x, (int) draw_position.y, rotation);

        level_->removeEntity(this);
    }

}
