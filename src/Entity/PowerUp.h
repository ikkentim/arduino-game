//
// Created by roelof on 1/7/16.
//
#include "BaseEntity.h"
#ifndef ARDUINOGAME_POWERUP_H
#define ARDUINOGAME_POWERUP_H

class Asteroid;
class PowerUp : public BaseEntity {
private:
    Asteroid* parent_;

public:
    PowerUp(Game *game, Level *level);
    //Always make base classes' destructors virtual when they're meant to be manipulated polymorphically.
    virtual ~PowerUp();

    //Updates this entity.
    virtual void update(const float& delta);

    //Render this entity.
    virtual void render();

    bool active;
    void reset(Asteroid* parent);

    //The position in the level
    Vector2 position;

    //Spawn a powerup with a one in {spawn_rate} chance
    uint8_t spawn_rate;

    static PowerUp* POWERUP = NULL;
    bool should_spawn();

    virtual void collided(BaseEntity* other);
};


#endif //ARDUINOGAME_POWERUP_H
