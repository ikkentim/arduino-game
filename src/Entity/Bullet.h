#include "BaseEntity.h"
#ifndef ARDUINOGAME_BULLET_H
#define ARDUINOGAME_BULLET_H

class Game;
class TestLevel;
class Player;

class Bullet : public BaseEntity {
public:
    Bullet(Game *game, TestLevel *level, Player *player);

	void update(const float& delta);
    void render();
    void collided(BaseEntity* other);

private:
    float default_velocity = 300.0f;
};

#endif //ARDUINOGAME_BULLET_H
