#ifndef ARDUINOGAME_ASTERIOID_H
#define ARDUINOGAME_ASTERIOID_H

#include "BaseEntity.h"

class Asteroid : public BaseEntity {

public:
    Asteroid(Game *game,const float max_speed=10.0f, const float min_speed=0.0f);
    void update(float delta);
    void render();
    void reset();
    bool destroyed;

    float max_speed;
    float min_speed;

};


#endif //ARDUINOGAME_ASTERIOID_H
