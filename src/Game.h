#ifndef ARDUINOGAME_GAME_H
#define ARDUINOGAME_GAME_H


#include "Engine.h"
#include "Level/Level.h"

class Level;

class Game : public Engine {
public:
    Game(Nunchuck *nunchuck, TFT *tft);
    void set_level(Level *level);

    Level *level;

protected:
    virtual void engine_update(float deltaTime);
    virtual void engine_render();

};


#endif //ARDUINOGAME_GAME_H
