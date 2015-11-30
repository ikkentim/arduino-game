#ifndef ARDUINOGAME_PLAYER_H
#define ARDUINOGAME_PLAYER_H


#include "BaseEntity.h"

class Player : public BaseEntity {

public:
    Player(Game *game);

    void update(float delta);
    void render(ShapeRenderer *renderer);

private:
    float move_speed_ = 5;
};


#endif //ARDUINOGAME_PLAYER_H
