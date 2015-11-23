#ifndef ARDUINOGAME_GAME_H
#define ARDUINOGAME_GAME_H


#include "Engine.h"

class Game : public Engine {
public:
    Game(Nunchuck *nunchuck, MI0283QT9 *tft) :
            Engine(nunchuck, tft) {
        test=0;
    }

protected:
    int test;
    virtual void engine_update();
    virtual void engine_render();
};


#endif //ARDUINOGAME_GAME_H
