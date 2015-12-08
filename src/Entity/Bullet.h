#include "BaseEntity.h"

#ifndef ARDUINOGAME_BULLET_H
#define ARDUINOGAME_BULLET_H

class Bullet : BaseEntity {
public:
    Bullet(Game *game);

    void update(float delta);
    void render();
};

#endif //ARDUINOGAME_BULLET_H
