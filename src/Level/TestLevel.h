#ifndef ARDUINOGAME_TESTLEVEL_H
#define ARDUINOGAME_TESTLEVEL_H

#include "../Level.h"
#include "../BaseEntity.h"
#include "../Player.h"

class TestLevel : public Level {
private:
    BaseEntity* testEntity_;
    Player* player_;
public:
    TestLevel(Game *game);
    ~TestLevel();
    void render(TFT *tft);
    void update(float deltaTime);
};


#endif //ARDUINOGAME_TESTLEVEL_H
