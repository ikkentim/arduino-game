//
// Created by Tim Potze on 23/11/15.
//

#include <stdio.h>
#include "Game.h"

void Game::engine_update() {
    nunchuck->update();
}

void Game::engine_render() {
    if(test < 128)
        tft->fillRect(5+(test < 128 ? test : 128 -(test-128)),5, 1,10, RGB(255,0,0));
    else
        tft->fillRect(5+(test < 128 ? test : 128 -(test-128)) + 9,5, 1,10, RGB(255,0,0));
    if(++test >= 256)test=0;
    tft->fillRect(5+(test < 128 ? test : 128 -(test-128)),5, 10,10, RGB(255,255,0));
}