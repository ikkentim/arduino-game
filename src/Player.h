#ifndef ARDUINOGAME_PLAYER_H
#define ARDUINOGAME_PLAYER_H


#include "BaseEntity.h"

class Player : public BaseEntity {

public:
    Player(Game *game);

    void update(float delta);
    void render();

private:
    float acceleration_ = 5;
    float move_speed_ = 0;
    float rotation_speed_ = 2;
};


#endif //ARDUINOGAME_PLAYER_H
