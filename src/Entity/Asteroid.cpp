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
    rotation += 0.1f * delta;
}

void Asteroid::render() {
    game_->sr.render(game_->tft, (int8_t *) shape1, 8, RGB(255, 255, 255),
                     (int) old_position.x, (int) old_position.y, old_rotation,
                     (int) position.x, (int) position.y, rotation);

    old_rotation = rotation;
    old_position = position;
}

Asteroid::Asteroid(Game *game,
                   const float max_speed=15.0f,
                   const float min_speed=2.0f
                  ) : BaseEntity(game) {

    this->min_speed = min_speed;
    this->max_speed = max_speed;
    reset();
}

void Asteroid::reset() {
    Random rand;
    //level->viewport->x y width height
    float vX, vY, vW, vH;
    vX = 0.0f;    vY = 0.0f;
    vW = 320;     vH = 240;

    Vector2 direction(
            rand.rand_float(0, 1.0f),
            rand.rand_float(0, 1.0f)
    );
    direction.normalize();

    direction.x = vW * direction.x;
    direction.y = vH * direction.y;

    position = direction * rand.rand_float(1.2f, 1.7f);


    velocity = Vector2(
            rand.rand_float(min_speed, max_speed),
            rand.rand_float(min_speed, max_speed)
    );

}
