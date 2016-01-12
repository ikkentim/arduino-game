#include "PowerUp.h"
#include <avr/pgmspace.h>
#include "../Random.h"
const int8_t diamond[] PROGMEM = {
        -8, 0, 0, -8,
        0, -8, 8, 0,
        8, 0, 0, 8,
        0, 8, -8, 0 //4
};

PowerUp::PowerUp(Game *game, Level *level)  : BaseEntity(game, level) {
    entity_type = TYPE_POWERUP;
    collision_check = false;
    collision_radius = 8;
    active = false;
    spawn_rate = 5;
}

PowerUp::~PowerUp()
{
}

void PowerUp::render() {
    if (active || old_active)
    {   //Render black powerup after it has been picked up
        Vector2 draw_position = position - level_->viewport.position();
        Color color = RGB(40, 160, 255);
        game_->sr.render(game_->tft, (int8_t *) diamond, 4, active ? color : 0,
                         old_draw_position_x, old_draw_position_y, 0,
                         (int) draw_position.x, (int) draw_position.y, 0);
        old_draw_position_x = (int)draw_position.x;
        old_draw_position_y = (int)draw_position.y;
    }
    old_active = active;
}


void PowerUp::update(const float &delta) {
    if (!level_->viewport.is_in_range(position, 30))
        active = false;
}

void PowerUp::reset(Vector2 position) {
    active = true;
    this->position = position;
}

bool PowerUp::should_spawn() {
    return !active && rand_uint8_t(0) < 255/spawn_rate;
}