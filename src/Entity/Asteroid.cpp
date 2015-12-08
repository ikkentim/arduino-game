#include "Asteroid.h"
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

Asteroid::Asteroid(Game *game) : BaseEntity(game) {
    position = Vector2(150, 50);
    collision_check = false;
    collision_radius = 16;
}

void Asteroid::collided(BaseEntity *other) {

}
