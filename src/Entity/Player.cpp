#include "Player.h"
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "../Level/TestLevel.h"
#include "../FastMath.h"
#include "Bullet.h"
#include "PowerUp.h"
#include "Asteroid.h"
#include "BaseEntity.h"
#include "../Level/GameOver.h"

#define FIRING_COOLDOWN 0.5f
#define POWERUP_INCREMENT 20

const int8_t playerShape[] PROGMEM = {
        -5, 6, 0, 0,
        -5, -6, 0, 0,
        -5, 6, 15, 0,
        -5, -6, 15, 0
};

Player::Player(Game *game, TestLevel *level) : BaseEntity(game, level) {
    entity_type = TYPE_PLAYER;
    position = Vector2(150, 150);

    collision_check = true;
    collision_radius = 16;
    has_powerup = false;
    dead_ = false;
}

void Player::update(const float& delta) {
    if (game_->nunchuck->button_z() && !dead_) {
        // add relative velocity so you get a drag effect
        velocity.y += fast_sin(rotation) * acceleration_ * delta;
        velocity.x += fast_cos(rotation) * acceleration_ * delta;
    } else {
        velocity += -velocity * deceleration_ * delta;
    }

    // Check if cooldown is active
    if (firing_cooldown_ > 0)
    {
        firing_cooldown_ -= delta;
    }
    // If cooldown isn't active, fire a bullet
    if (game_->nunchuck->button_c() && firing_cooldown_ <= 0 && !dead_)
    {
        level_->addEntity(new Bullet(game_, level_, this));

        firing_cooldown_ = FIRING_COOLDOWN;
    }

    // if speed is faster than max speed, clamp it
    if (velocity.length_sq() > square(max_speed_)) {
        velocity = velocity.normalized() * max_speed_;
    }

    // add rotations
    if(!dead_){
        rotation += game_->nunchuck->joystick().x * rotation_speed_ * delta;
    }

    position = position + velocity * delta;

}

void Player::render() {
    Vector2 draw_position = position - level_->viewport.position();
    if (has_powerup)
        powerup_frame_ += POWERUP_INCREMENT;
    
    game_->sr.render(game_->tft, (int8_t *) playerShape, 4, 
                     RGB(200, 200+abs(powerup_frame_/(255/55)), 200+abs(powerup_frame_/(255/55))),
                     old_draw_position_x, old_draw_position_y, old_rotation,
                     (int) draw_position.x, (int) draw_position.y, 
                     rotation);

    old_rotation = rotation;
    old_draw_position_x = (int)draw_position.x;
    old_draw_position_y = (int)draw_position.y;
}

void Player::collided(BaseEntity *other) {
    if (other->entity_type == TYPE_POWERUP)
    {
        dead_ = true;
        PowerUp* pupp = ((PowerUp*)other);
        if (pupp->active)
        {
            pupp->active = false;
            has_powerup = true;
            powerup_frame_ = 0;
        }
    }
    else if (other->entity_type == TYPE_ASTEROID)
    {
        if (has_powerup)
        {
            has_powerup = false;
            powerup_frame_ = 0;
            ((Asteroid*)other)->reset(true);
        }
        else
        {
            dead_ = true;
            game_->set_level(new GameOver(game_)); //call this method last
        }

    }
}

