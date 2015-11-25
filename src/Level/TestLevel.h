#ifndef ARDUINOGAME_TESTLEVEL_H
#define ARDUINOGAME_TESTLEVEL_H

#include "../Level.h"

class TestLevel : public Level {
public:
    TestLevel(Game *game);
    void render(MI0283QT9 *tft);
    void update();
};


#endif //ARDUINOGAME_TESTLEVEL_H
