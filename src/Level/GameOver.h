#ifndef ARDUINOGAME_GAMEOVER_H
#define ARDUINOGAME_GAMEOVER_H


#include "Level.h"

class GameOver : public Level{
public:
    GameOver(Game *game);
    void update(float delta);
    void pre_render();
    void render();

};


#endif //ARDUINOGAME_GAMEOVER_H
