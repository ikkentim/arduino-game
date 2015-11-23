//
// Created by Tim Potze on 23/11/15.
//

#include <stdio.h>
#include "Game.h"

void Game::engine_update() {
    nunchuck->update();
}

void Game::engine_render() {
    char buf[64];
    sprintf(buf, "Z: %d, C: %d fps: %d", nunchuck->button_z(), nunchuck->button_c(), fps);

    tft->drawText(5, 5, buf, RGB(255, 255, 255), RGB(255, 0, 0), 1);

    Vector3 a = nunchuck->acceleration();
    sprintf(buf, "acc:(%d, %d, %d)         ", (int) (a.x * 1000), (int) (a.y * 1000), (int) (a.z * 1000));
    tft->drawText(5, 15, buf, RGB(255, 255, 255), RGB(255, 0, 0), 1);

    Vector2 j = nunchuck->joystick();
    sprintf(buf, "joy:(%d, %d)      ", (int) (j.x * 1000), (int) (j.y * 1000));
    tft->drawText(5, 25, buf, RGB(255, 255, 255), RGB(255, 0, 0), 1);
}