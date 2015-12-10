#ifndef ARDUINOGAME_TESTLEVEL_H
#define ARDUINOGAME_TESTLEVEL_H

#include <stdint.h>
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

    static const uint8_t MAX_ASTEROID_COUNT;
public:
    Viewport viewport;
    TestLevel(Game *game);
    ~TestLevel();
    void render();
    void update(float deltaTime);
};


#endif //ARDUINOGAME_TESTLEVEL_H
