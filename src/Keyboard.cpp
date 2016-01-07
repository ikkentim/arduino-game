#include "Keyboard.h"

#define LETTER_SIZE 24
#define START_X 40
#define PINCREMENT_X 12
#define START_Y 150
#define CURSOR_RADIUS 3

const char* letters = (char *) "qwertyuiop\nasdfghjkl\nzxcvbnm";

Keyboard::Keyboard(Game *game, Level *level) : BaseEntity(game, level) {

}

void Keyboard::update(const float &delta) {
    Vector2 nuchuck_position = game_->nunchuck->joystick();

    cursor_position.x = nuchuck_position.x * (320.0f / 2) + 160.0f;
    cursor_position.y = -nuchuck_position.y * (120.0f / 2) + 180.0f;
}

void Keyboard::render() {
    // render de oude cursor weer zwart zodat hij niet meer zichtbaar is
    game_->tft->fillCircle(old_cursor_position.x, old_cursor_position.y, CURSOR_RADIUS, RGB(0, 0, 0));

    int check[4];
    int i = 0;

    /*
     * Omdat de oude cursor zwart is kunnen maximaal 4 letters een deel missen
     * Deze letters moeten berekend worden zodat deze opnieuw kunnen worden gerenderd
     * Loop om de cursor heen om letters te checken
     */
    for(int x = -CURSOR_RADIUS; x <= CURSOR_RADIUS; x += CURSOR_RADIUS) {
        for(int y = -CURSOR_RADIUS; y <= CURSOR_RADIUS; y++) {
            if(x == 0 && y == 0 || abs(x) xor abs(y))
                continue;

            int char_index = get_char_from_position(Vector2(old_cursor_position.x + x, old_cursor_position.y + y));

            if(char_index != -1) {
                bool found = false;
                for (int j = 0; j < i; ++j) {
                    if(check[j] == char_index) {
                        found = true;
                    }
                }

                check[i++] = char_index;

                if(!found)
                    render_char(char_index);
            }
        }
    }
    
    game_->tft->fillCircle(cursor_position.x, cursor_position.y, CURSOR_RADIUS, RGB(255, 0, 0));

    old_cursor_position = cursor_position;
}

void Keyboard::render_char(int index) {
    int l, t;

    // de posities van de rijen zijn hardcoded, omdat een toetsenbord toch nooit veranderd
    if(index > 20) {
        t = 2;
        l = index - 21;
    } else if(index > 10) {
        t = 1;
        l = index - 11;
    } else {
        t = 0;
        l = index;
    }

    game_->tft->drawChar(l * LETTER_SIZE + START_X + t * PINCREMENT_X,
                         t * LETTER_SIZE + START_Y,
                         letters[index],
                         RGB(255, 255, 255),
                         RGB(0, 0, 0),
                         LETTER_SIZE / 8);
}

void Keyboard::collided(BaseEntity *other) {

}

bool Keyboard::is_pressed() {
    return game_->nunchuck->button_z();
}

char Keyboard::get_pressed_char() {
    int char_index = get_char_from_position(cursor_position);

    if(char_index != -1) {
        return letters[char_index];
    }

    return '\0';
}

int Keyboard::get_char_from_position(Vector2 position) {
    // normaliseer x en y met de start positie van het keyboard
    int y = (int)position.y - START_Y;
    int x = (int)position.x - START_X;

    // de rij van de letter is simpelweg te berekenen hoevaak een letter size in de y positie past
    int row = y / LETTER_SIZE;

    // als het buiten het toetsenbord valt, rij -1 of 3, hebben we geen letter
    if(row < 0 || row > 2){
        return -1;
    }

    /*
     * Omdat het toetsenbord inspringt zijn de x posities wat meer hardcoded
     * De x wordt eerst gereset met het inspringen van het toetsenbord
     * Daarna wordt gekeken hoe vaak de letter size in de x past
     * Vervolgens wordt er hardcoded gekeken hoeveel letters er in een rij bevinden
     * return -1 als het niet in de rij past
     */
    x -= row * PINCREMENT_X;

    int col = x / LETTER_SIZE;

    switch(row) {
        case 0:
            return (col >= 0 && col < 10) ? col : -1;
        case 1:
            return (col >= 0 && col < 9) ? col + 11 : -1;
        case 2:
            return (col >= 0 && col < 7) ? col + 21 : -1;
        default:
            return -1;
    }
}

void Keyboard::pre_render() {
    for (int i = 0; i < strlen(letters); i++){
        if(letters[i] == '\n') {
            continue;
        }

        render_char(i);
    }
}

bool Keyboard::is_backspace_pressed() {
    return game_->nunchuck->button_c();
}
