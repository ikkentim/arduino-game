#ifndef ARDUINOGAME_KEYBOARD_H
#define ARDUINOGAME_KEYBOARD_H


#include "Entity/BaseEntity.h"

class Keyboard : public BaseEntity {
public:
    Keyboard(Game *game, Level *level);
    virtual void update(const float & delta);
    virtual void render();
    virtual void collided(BaseEntity* other);
    void render_char(int index);
    bool is_pressed();
    char get_pressed_char();
    void pre_render();

    bool is_backspace_pressed();

private:
    Vector2 old_cursor_position;
    Vector2 cursor_position;
    int get_char_from_position(Vector2 position);
};


#endif //ARDUINOGAME_KEYBOARD_H
