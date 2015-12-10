#include "BaseEntity.h"

#ifndef ARDUINOGAME_BULLET_H
#define ARDUINOGAME_BULLET_H

class Game;
class TestLevel;
class Player;

class Bullet : public BaseEntity {
public:
    Bullet(Game *game, Player *player, TestLevel *level);

    void update(float delta);
    void render();
    void collided(BaseEntity* other);
private:
    // Default bullet speed, playerVelocity will be added to it
    float defaultVelocity = 2.0f;
};

#endif //ARDUINOGAME_BULLET_H
