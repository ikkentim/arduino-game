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
        return true;
    }

    return false;
}