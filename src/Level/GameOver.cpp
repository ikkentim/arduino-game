#include <stdlib.h>
#include <string.h>
#include <EEPROM.h>
#include "GameOver.h"
#include "../Color.h"
#include "../Game.h"
#include "MenuLevel.h"
#include "../Keyboard.h"
#include "../Highscore.h"

GameOver::GameOver(Game *game) : Level(game) {
    Highscore highscore;
    EEPROM.begin();
    EEPROM.get(0, highscore);
    EEPROM.end();

    if (!highscore.is_valid() || game->score->get_score() > highscore.score) {
        keyboard_ = new Keyboard(game, this);

        addEntity(keyboard_);

        sprintf(name, "___");

        game->nunchuck->calibrate = false;

        last_frame_pressed = true;
        last_frame_backspace_pressed = false;
    }
    else {
        keyboard_ = 0;
    }
}

void GameOver::update(float delta) {

    if (keyboard_ != 0) {
        keyboard_->update(delta);

        if (name_index == 3) {
            if (keyboard_->is_pressed() && !last_frame_pressed) {
                Highscore highscore;
                highscore.score = game->score->get_score();
                for (int i = 0; i < 4; i++)
                    highscore.name[i] = name[i] == '_' ? (char) '\0' : name[i];
                EEPROM.begin();
                EEPROM.put(0, highscore);
                EEPROM.end();

                game->nunchuck->calibrate = true;
                delete keyboard_;
                keyboard_ = 0;
                game->set_level(new MenuLevel(game));
                return;
            } else if (!keyboard_->is_pressed()) {
                last_frame_pressed = false;
            }
        }
        else {
            if (keyboard_->is_pressed() && !last_frame_pressed) {
                name[name_index++] = keyboard_->get_pressed_char();

                last_frame_pressed = true;
            } else if (!keyboard_->is_pressed()) {
                last_frame_pressed = false;
            }
        }

        if (keyboard_->is_backspace_pressed() && !last_frame_backspace_pressed && name_index > 0) {
            name[--name_index] = '_';
            last_frame_backspace_pressed = true;
        } else if (!keyboard_->is_backspace_pressed()) {
            last_frame_backspace_pressed = false;
        }
    } else {
        if (game->nunchuck->button_z() && !last_frame_pressed) {
            game->nunchuck->calibrate = true;
            game->set_level(new MenuLevel(game));
            return;
        } else if (!game->nunchuck->button_z() ) {
            last_frame_pressed = false;
        }
    }
}

void GameOver::render() {
    if (keyboard_ != 0) {
        game->tft->drawText(game->tft->lcd_width / 2 - 48, game->tft->lcd_height / 2 - 40, name, RGB(255, 255, 255),
                            RGB(0, 0, 0), 4);

        keyboard_->render();
    }
}

void GameOver::pre_render() {
    const char *text = "Game Over";
    const uint8_t title_size = 4;

    float left, top;
    Color randColor, black, white;

    randColor = RGB(255, rand() % 150, rand() % 150);
    black = RGB(0, 0, 0);
    white = RGB(255, 255, 255);

    left = (game->tft->lcd_width / 2) - (((float) strlen(text) / 2) * 8 * title_size);
    top = game->tft->lcd_height / 6;
    // Render the coolest title in the world (Math to center it horizontally, the 8 is because of 8 bits)
    game->tft->drawText(left, top, text, randColor, black, title_size);

    char buf[32];
    sprintf(buf, "Your score: %d", game->score->get_score());


    left = (game->tft->lcd_width / 2) - (((float) strlen(buf) / 2) * 8);
    top = game->tft->lcd_height / 2;
    game->tft->drawText(left, top, buf, white, black, 1);

    if (keyboard_ != 0) {
        keyboard_->pre_render();
    }
}
