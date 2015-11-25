#include <stdio.h>
#include "Engine.h"

#define RATE_RENDER     (30)
#define RATE_UPDATE     (30)

Engine::Engine(Nunchuck *n, MI0283QT9 *t) {
    nunchuck=n;
    tft=t;
    awaitRender_ = false;
    awaitUpdate_ = false;
    timeSinceRender_ = 0;
    timeSinceUpdate_ = 0;
}

void Engine::tick(float timeElapsed) {
    timeSinceRender_ += timeElapsed;
    timeSinceUpdate_ += timeElapsed;

    if (timeSinceRender_ > 1.0f / RATE_RENDER) {
        timeSinceRender_ -= 1.0f / RATE_RENDER;
        awaitRender_ = true;
    }

    if (timeSinceUpdate_ > 1.0f / RATE_UPDATE) {
        awaitUpdate_ = true;
    }
}

bool Engine::update() {
    if (awaitUpdate_) {
        awaitUpdate_ = false;
        engine_update();
        timeSinceUpdate_ = 0;
    }

    if (awaitRender_) {
        awaitRender_ = false;
        engine_render();
        display_free_ram();
        return true;
    }

    return false;
}

void Engine::display_free_ram() {
    extern int __heap_start, *__brkval;
    int v;
    int freeRam = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);

    char buf[14];

    sprintf(buf, "Free mem: %d", freeRam);

    tft->drawText(2, 2, buf, RGB(0, 0, 0), RGB(255, 0, 0), 1);
}
