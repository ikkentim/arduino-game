#ifndef ARDUINOGAME_TESTLEVEL_H
#define ARDUINOGAME_TESTLEVEL_H

#include "Level.h"
#include "../Viewport.h"

class Asteroid;
class Player;
class Game;

class TestLevel : public Level {
private:
    Player* player_;
    Asteroid* testAsteroid_;

    void update_viewport();
public:
    Viewport viewport;
    TestLevel(Game *game);
    ~TestLevel();
    void render();
    void update(float delta);
};


#endif //ARDUINOGAME_TESTLEVEL_H
