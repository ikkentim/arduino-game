//
// Created by roelof on 1/7/16.
//
#include "BaseEntity.h"
#ifndef ARDUINOGAME_POWERUP_H
#define ARDUINOGAME_POWERUP_H

class Asteroid;
class PowerUp : public BaseEntity {
private:
    bool old_active;
public:
    PowerUp(Game *game, Level *level);
    ~PowerUp();
    //Updates this entity.
    virtual void update(const float& delta);

    //Render this entity.
    virtual void render();

    bool active;
    void reset(Vector2 position);

    //The position in the level
    Vector2 position;

    //Spawn a powerup with a one in {spawn_rate} chance
    uint8_t spawn_rate;

    static PowerUp* POWERUP;
    bool should_spawn();

};


#endif //ARDUINOGAME_POWERUP_H
