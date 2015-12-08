#ifndef ARDUINOGAME_TESTLEVEL_H
#define ARDUINOGAME_TESTLEVEL_H

#include "../Level.h"
#include "../BaseEntity.h"
#include "../Viewport.h"

class Asteroid;
class Player;

class TestLevel : public Level {
private:
    BaseEntity* testEntity_;
    Player* player_;
    Asteroid* testAsteroid_;

    void update_viewport();
public:
    Viewport viewport;
    TestLevel(Game *game);
    ~TestLevel();
    void render();
    void update(float deltaTime);
};


#endif //ARDUINOGAME_TESTLEVEL_H
