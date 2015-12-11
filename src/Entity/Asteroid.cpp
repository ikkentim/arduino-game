#include "Asteroid.h"
#include "../Random.h"
#include <avr/pgmspace.h>

const int8_t shape1[] PROGMEM = {
    -15,  0, -1, -3,
     -1, -3,  0,-15,
      0,-15, 10,-10,
     10,-10, 15,  0,
     15,  0, 12, 11,
     12, 11,  0, 15,
      0, 15,-10, 10,
    -10, 10,-15,  0
};


void Asteroid::update(float delta) {
    position += velocity * delta;
}

void Asteroid::render() {
    Vector2 draw_position = position - level_->viewport.position();

    game_->sr.render(game_->tft, (int8_t *) shape1, 8, RGB(255, 255, 255),
                     (int) old_position.x, (int) old_position.y, old_rotation,
                     (int) position.x, (int) position.y, rotation);

    old_rotation = rotation;
    old_position = position;
}

Asteroid::Asteroid(Game *game, TestLevel *level,
                   const float max_speed,
                   const float min_speed
                  ) : BaseEntity(game, level) {
    collision_check = false;
    collision_radius = 16;
    this->min_speed = min_speed;
    this->max_speed = max_speed;
    reset();
}

void Asteroid::reset() {
    Random rand;

    Vector2 viewport_position = level_->viewport.position();
    Vector2 viewport_size = level_->viewport.size();

    Vector2 direction(
            rand.rand_float(0, 1.0f),
            rand.rand_float(0, 1.0f)
    );
    direction.normalize();

    position = direction * viewport_size;

    position = position * rand.rand_float(1.2f, 1.7f);

    position = viewport_position + position; //convert to global position

    velocity = Vector2(
            rand.rand_float(0.0f, 1.0f),
            rand.rand_float(0.0f, 1.0f)
    );

    velocity.normalize();
    velocity = velocity * ( direction + Vector2(0.5f, 0.5f) );

    velocity.normalize();
    velocity = velocity * rand.rand_float(min_speed, max_speed);
}

void Asteroid::collided(BaseEntity *other) {

}
