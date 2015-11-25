#include <stdio.h>
#include "Game.h"
#include "Level/TestLevel.h"

int freeRam ()
{
}

Game::Game(Nunchuck *nunchuck, MI0283QT9 *tft) : Engine(nunchuck, tft) {
    this->level = new TestLevel(this);
}

void Game::engine_update() {
    nunchuck->update();

    if(this->level != 0){
        this->level->update();
    }
}

void Game::engine_render() {
    if(this->level != 0) {
        this->level->render(tft);
    }

    extern int __heap_start, *__brkval;
    int v;
    int freeRam = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);

    char buf[14];

    sprintf(buf, "Free mem: %d", freeRam);

    tft->drawText(0, 25, buf, RGB(0, 0, 0), RGB(255, 0, 0), 1);
}

void Game::setLevel(Level *level) {
    if (this->level != 0) {
        delete this->level;
        this->level = 0;
    }

    this->level = level;
}
