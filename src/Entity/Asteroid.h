#ifndef ARDUINOGAME_ASTERIOID_H
#define ARDUINOGAME_ASTERIOID_H

#include "BaseEntity.h"

class Asteroid : public BaseEntity {

public:
    Asteroid(Game *game);
    void update(float delta);
    void render();

};


#endif //ARDUINOGAME_ASTERIOID_H
