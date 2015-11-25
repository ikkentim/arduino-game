#ifndef ARDUINOGAME_TESTLEVEL_H
#define ARDUINOGAME_TESTLEVEL_H

#include "../Level.h"
#include "../BaseEntity.h"
class TestLevel : public Level {
private:
    BaseEntity* testEntity_;
public:
    TestLevel(Game *game);
    ~TestLevel();
    void render(MI0283QT9 *tft);
    void update();
};


#endif //ARDUINOGAME_TESTLEVEL_H
