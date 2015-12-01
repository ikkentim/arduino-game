#ifndef ARDUINOGAME_LEVEL_H
#define ARDUINOGAME_LEVEL_H

#include "Game.h"

class Game;

class Level {
public:
    Level(Game *game);
    virtual ~Level();
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

protected:
    Game *game;
};


#endif //ARDUINOGAME_LEVEL_H
