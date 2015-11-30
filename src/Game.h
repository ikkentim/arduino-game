#ifndef ARDUINOGAME_GAME_H
#define ARDUINOGAME_GAME_H


#include "Engine.h"
#include "Level.h"

class Level;

class Game : public Engine {
public:
    Game(Nunchuck *nunchuck, TFT *tft);
    void set_level(Level *level);

protected:
    virtual void engine_update();
    virtual void engine_render();

private:
    Level *level;
};


#endif //ARDUINOGAME_GAME_H
