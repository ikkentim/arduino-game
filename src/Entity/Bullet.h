#include "BaseEntity.h"
#ifndef ARDUINOGAME_BULLET_H
#define ARDUINOGAME_BULLET_H

class Game;
class TestLevel;

class Bullet : BaseEntity {
public:
    Bullet(Game *game, TestLevel *level);

    void update(float delta);
    void render();
};

#endif //ARDUINOGAME_BULLET_H
