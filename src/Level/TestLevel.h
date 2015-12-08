#ifndef ARDUINOGAME_TESTLEVEL_H
#define ARDUINOGAME_TESTLEVEL_H

#include "Level.h"
#include "../Entity/BaseEntity.h"
#include "../Entity/Player.h"
#include "../Entity/Asteroid.h"

class TestLevel : public Level {
private:
    BaseEntity* testEntity_;
    Player* player_;
    Asteroid* testAsteroid_;
public:
    TestLevel(Game *game);
    ~TestLevel();
    void render();
    void update(float deltaTime);
};


#endif //ARDUINOGAME_TESTLEVEL_H
