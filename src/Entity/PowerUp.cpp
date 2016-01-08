#include "PowerUp.h"
#include <avr/pgmspace.h>
#include "Asteroid.h"
#include "../Random.h"
PowerUp* PowerUp::POWERUP = NULL;
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

    POWERUP = this;
    spawn_rate = 1;
}

PowerUp::~PowerUp()
{
    if (POWERUP == this)
        POWERUP = NULL;
}

void PowerUp::render() {
    if (active || old_active)
    {   //Render negative of powerup after it has been picked up
        Vector2 draw_position = position - level_->viewport.position();
        Color color = RGB(40, 160, 255);
        game_->sr.render(game_->tft, (int8_t *) diamond, 4, active ? color : 0,
                         (int) draw_position.x, (int) draw_position.y, 0,
                         (int) draw_position.x, (int) draw_position.y, 0);
    }
    old_active = active;
}


void PowerUp::update(const float &delta) {
}

void PowerUp::reset(Vector2 position) {
    active = true;
    this->position = position;
}

bool PowerUp::should_spawn() {
    return !active && rand_uint8_t(0) < 255/spawn_rate;
}