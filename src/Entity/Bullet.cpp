#include "Bullet.h"
#include "../FastMath.h"
#include <avr/pgmspace.h>
#include "Player.h"
#include "Asteroid.h"
#include "../Random.h"

#define DEFAULT_VELOCITY 300.0f

const int8_t bulletShape[] PROGMEM = {
        0, 2, 0, 0
};

Bullet::Bullet(Game *game, Level *level, Player *player) : BaseEntity(game, level) {
    entity_type = TYPE_BULLET;

    collision_check = true;
    collision_radius = 1;
    rotation = player->rotation;
    // Calculate velocity depending on player rotation and velocity
    velocity.x = fast_cos(rotation) * DEFAULT_VELOCITY + player->velocity.x;
    velocity.y = fast_sin(rotation) * DEFAULT_VELOCITY + player->velocity.y;
    position.x = player->position.x + fast_cos(rotation) * 25;
    position.y = player->position.y + fast_sin(rotation) * 25;
}

void Bullet::render() {
    Vector2 draw_position = position - level_->viewport.position();

    game_->sr.render(game_->tft, (int8_t *) bulletShape, 1, RGB(255, 120, 0), old_position_x,
                    old_position_y, rotation, (int) draw_position.x, (int) draw_position.y, rotation);


	old_position_x = draw_position.x;
	old_position_y = draw_position.y;
}

void Bullet::update(const float& delta) {
    position = position + velocity * delta;

    // Check if bullet exits viewport, if so, remove the bullet
    if (!level_->viewport.is_in_range(position, 30))
    {
        level_->removeEntity(this);
    }
}

void Bullet::collided(BaseEntity *other) {
    if (other->entity_type == TYPE_ASTEROID) {
        Asteroid* asteroid = ((Asteroid*) other);
        if (rand_uint8_t(0) > 200 && )
            ->reset();

        Vector2 draw_position = position - level_->viewport.position();
        game_->sr.render(game_->tft, (int8_t *) bulletShape, 1, RGB(0, 0, 0), (int) (old_position_x),
                         (int) old_position_y, rotation, (int) draw_position.x, (int) draw_position.y, rotation);

        game_->score->add_score(3);
        level_->removeEntity(this);
    }

}
