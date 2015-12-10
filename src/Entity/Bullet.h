#include "BaseEntity.h"

#ifndef ARDUINOGAME_BULLET_H
#define ARDUINOGAME_BULLET_H

class Game;
class TestLevel;
class Player;

class Bullet : BaseEntity {
public:
    Bullet(Game *game, Player *player, TestLevel *level);

    void update(float delta);
    void render();
private:
    // Default bullet speed, playerVelocity will be added to it
    float defaultVelocity = 0.2f;
};

#endif //ARDUINOGAME_BULLET_H
