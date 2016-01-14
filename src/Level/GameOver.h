#ifndef ARDUINOGAME_GAMEOVER_H
#define ARDUINOGAME_GAMEOVER_H


#include "Level.h"
#include "../Keyboard.h"

class GameOver : public Level{
public:
    GameOver(Game *game);
    void update(float delta);
    void pre_render();
    void render();

private:
    Keyboard *keyboard_;
    char name[4];
    uint8_t name_index = 0;
    bool last_frame_pressed;
    bool last_frame_backspace_pressed;
};


#endif //ARDUINOGAME_GAMEOVER_H
