#ifndef ARDUINOGAME_GAME_H
#define ARDUINOGAME_GAME_H


#include "Engine.h"
#include "Level/Level.h"
#include "Score.h"

class Level;

class Game : public Engine {
public:
    Game(Nunchuck *nunchuck, TFT *tft);
    void set_level(Level *level);

    Level *level;
    Score *score;

protected:
    virtual void engine_update(float deltaTime);
    virtual void engine_render();
    virtual void collision_detection();

};


#endif //ARDUINOGAME_GAME_H
