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
    -10, 10,-15,  0//8
};

const int8_t shape2[] PROGMEM = {
     -9,-15,  3,-15,
      3,-15, 15, -9,
     15, -9, 15, -3,
     15, -3,  0,  0,
      0,  0, 15,  9,
     15,  9,  3, 15,
      3, 15,  0, 12,
      0, 12, -9, 15,
     -9, 15,-15,  6,
     -15, 6, -15,-6,
     -15, -6,-3, -6,
     -3, -6, -9,-15//12
};

const int8_t shape3[] PROGMEM = {
     -6,-12,  0, -6,
      0, -6,  6,-12,
      6,-12, 15, -6,
     15, -6,  9, -3,
      9, -3, 15,  3,
     15,  3,  9, 12,
      9, 12,  0,  9,
      0,  9, -3, 12,
     -3, 12,-12,  9,
    -12,  9, -9,  3,
     -9,  2,-12, -6,
    -12, -6, -6,-12//12
};


void Asteroid::update(float delta) {
    //rotation += 0.1f * delta;
}

void Asteroid::render() {
    Vector2 draw_position = position - level_->viewport.position();

    game_->sr.render(game_->tft, (int8_t *) shape1, 8, RGB(255, 255, 255),
                     (int) old_position.x, (int) old_position.y, old_rotation,
                     (int) draw_position.x, (int) draw_position.y, rotation);

    old_rotation = rotation;
    old_position = draw_position;
}

Asteroid::Asteroid(Game *game, TestLevel *level) : BaseEntity(game, level) {
    position = Vector2(150, 50);
    collision_check = false;
    collision_radius = 16;
}

void Asteroid::collided(BaseEntity *other) {

}
