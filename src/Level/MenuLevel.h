#ifndef ARDUINOGAME_MENULEVEL_H
#define ARDUINOGAME_MENULEVEL_H

#include "../Level.h"


class MenuLevel : public Level {
public:
    MenuLevel(Game *game);
    void render(MI0283QT9 *tft);
    void update();
private:
    const char *menu_title_ = "Asteroids";
};

#endif //ARDUINOGAME_MENULEVEL_H
