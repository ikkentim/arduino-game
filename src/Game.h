#ifndef ARDUINOGAME_GAME_H
#define ARDUINOGAME_GAME_H


#include "Engine.h"

class Game : public Engine {
public:
    Game(Nunchuck *nunchuck, MI0283QT9 *tft) :
            Engine(nunchuck, tft) {
    }

protected:
    virtual void engine_update() override;
    virtual void engine_render() override;
};


#endif //ARDUINOGAME_GAME_H
