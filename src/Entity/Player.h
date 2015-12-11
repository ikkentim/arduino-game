#ifndef ARDUINOGAME_PLAYER_H
#define ARDUINOGAME_PLAYER_H


#include "BaseEntity.h"
#include "../Game.h"

class Bullet;

class Player : public BaseEntity {

public:
    Player(Game *game, TestLevel *level);

	void update(const float& delta);
    void render();
    void collided(BaseEntity* other);

private:
    float acceleration_ = 70;
    float deceleration_ = 0.90f;
    float max_speed_ = 200;
    float rotation_speed_ = 3;
    float firing_cooldown_ = 0;
    bool dead_;
};


#endif //ARDUINOGAME_PLAYER_H
