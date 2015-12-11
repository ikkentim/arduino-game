#ifndef ARDUINOGAME_ASTERIOID_H
#define ARDUINOGAME_ASTERIOID_H

#include "BaseEntity.h"

class Asteroid : public BaseEntity {

public:
    Asteroid(Game *game, TestLevel *level, const float max_speed=50.0f, const float min_speed=10.0f);
    void update(float delta);
    void render();
    void collided(BaseEntity* other);
    void reset();
    bool destroyed;

    float max_speed;
    float min_speed;


};


#endif //ARDUINOGAME_ASTERIOID_H
