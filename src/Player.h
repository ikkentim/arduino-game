#ifndef ARDUINOGAME_PLAYER_H
#define ARDUINOGAME_PLAYER_H


#include "BaseEntity.h"

class Player : public BaseEntity {

public:
    Player(Game *game, TestLevel *level);

    void update(float delta);
    void render();

private:
    float acceleration_ = 70;
    float deceleration_ = 0.90f;
    float max_speed_ = 200;
    float rotation_speed_ = 3;
};


#endif //ARDUINOGAME_PLAYER_H
