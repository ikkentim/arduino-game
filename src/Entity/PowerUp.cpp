#include "PowerUp.h"
#include <avr/pgmspace.h>
#include "Asteroid.h"
#include "../Random.h"

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
    POWERUP = this;
    spawn_rate = 1;
}

PowerUp::~PowerUp()
{
    if (POWERUP == this)
        POWERUP = NULL;
}

void PowerUp::render() {
    if (!active)
        return;

    Vector2 draw_position = position - level_->viewport.position();
    game_->sr.render(game_->tft, (int8_t *)diamond, 4, RGB(0, 120, 255),
                     (int)draw_position.x, (int)draw_position.y, 0,
                     (int)draw_position.x, (int)draw_position.y, 0);
}

void PowerUp::collided(BaseEntity *other) { }


void PowerUp::update(const float &delta) { 
}

void PowerUp::reset(Asteroid *parent) {
    parent_ = parent;
    active = true;
    this->position = parent->position;
}

bool PowerUp::should_spawn() {
    return !active && rand_uint8_t(0) < 255/spawn_rate;    
}
