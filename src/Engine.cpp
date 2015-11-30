#include <stdio.h>
#include "Engine.h"

#define RATE_RENDER     (30)
#define RATE_UPDATE     (30)

Engine::Engine(Nunchuck *n, TFT *t) {
    nunchuck = n;
    tft = t;
    awaitRender_ = false;
    awaitUpdate_ = false;
    timeSinceRender_ = 0;
    timeSinceUpdate_ = 0;
    timeSinceFps_ = 0;
    fps_ = 0;
    frames_ = 0;
    awaitDebug_ = true;
}

void Engine::tick(float timeElapsed) {
    timeSinceRender_ += timeElapsed;
    timeSinceUpdate_ += timeElapsed;
    timeSinceFps_ += timeElapsed;

    if (timeSinceRender_ > 1.0f / RATE_RENDER) {
        timeSinceRender_ -= 1.0f / RATE_RENDER;
        awaitRender_ = true;
    }

    if (timeSinceUpdate_ > 1.0f / RATE_UPDATE) {
        awaitUpdate_ = true;
    }

    if (timeSinceFps_ > 1.0f) {
        fps_ = frames_;
        frames_ = 0;
        timeSinceFps_ -= 1.0f;
        awaitDebug_ = true;
    }
}

bool Engine::update() {
    if (awaitUpdate_) {
        awaitUpdate_ = false;
        engine_update();
        timeSinceUpdate_ = 0;
    }

    if (awaitRender_ || true) {
        awaitRender_ = false;
        frames_++;
        engine_render();
        display_free_ram();
        return true;
    }

    return false;
}

void Engine::display_free_ram() {
    if (awaitDebug_) {
        extern int __heap_start, *__brkval;
        int v;
        int freeRam = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);

        char buf[32];
        sprintf(buf, "Free mem: %d, %d fps    ", freeRam, fps_);

        tft->drawText(2, 2, buf, RGB(255, 255, 255), RGB(0, 0, 0), 1);
        awaitDebug_ = false;
    }
}
