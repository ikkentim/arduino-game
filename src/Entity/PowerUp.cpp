#include "PowerUp.h"
#include <avr/pgmspace.h>
#include "Asteroid.h"

const int8_t diamond[] PROGMEM = {
        -8, 0, 0, -8,
        0, -8, 8, 0,
        8, 0, 8, 0,
        8, 0, -8, 0 //4
};

PowerUp::PowerUp(Game *game, Level *level)  : BaseEntity(game, level) {
    entity_type = TYPE_POWERUP;
    collision_check = false;
    collision_radius = 16;
    parent_ = NULL;
    Asteroid::POWERUP = this;
}

PowerUp::~PowerUp()
{
    Asteroid::POWERUP = NULL;
}

void PowerUp::render() {
    if (!active)
        return;

    Vector2 draw_position = position - level_->viewport.position();
    game_->sr.render(game_->tft, (int8_t *)diamond, 4, RGB(0, 120, 255),
                     old_position_x, old_position_y, old_rotation,
                     (int)draw_position.x, (int)draw_position.y, rotation);
}

void PowerUp::collided(BaseEntity *other) { }


void PowerUp::update(const float &delta) {
    old_position_x = position.x;
    old_position_y = position.y;
}

void PowerUp::reset(Asteroid *parent) {
    parent_ = parent;
    active = true;
    this->position = parent->position;
}
