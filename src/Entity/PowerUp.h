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
    virtual ~BaseEntity() { };

    //Updates this entity.
    virtual void update(const float& delta);

    //Render this entity.
    virtual void render();

    bool active;
    void reset(Asteroid* parent);

    //The position in the level
    Vector2 position;
    int old_position_x;
    int old_position_y;

    bool collision_check;
    uint8_t collision_radius;
    virtual void collided(BaseEntity* other);
    EntityType entity_type;
};


#endif //ARDUINOGAME_POWERUP_H
