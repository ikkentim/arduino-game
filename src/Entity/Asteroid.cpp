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
