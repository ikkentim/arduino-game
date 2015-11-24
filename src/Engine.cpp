#include "Engine.h"

#define RATE_RENDER     (30)
#define RATE_UPDATE     (50)

Engine::Engine(Nunchuck *n, MI0283QT9 *t) {
    nunchuck=n;
    tft=t;
    fps=0;
    awaitRender_ = false;
    awaitUpdate_ = false;
    timeSinceRender_ = 0;
    timeSinceUpdate_ = 0;
    timeSinceFps_ = 0;
    framesSinceFps_ = 0;
}

void Engine::tick(float timeElapsed) {
    timeSinceRender_ += timeElapsed;
    timeSinceUpdate_ += timeElapsed;

    if (timeSinceRender_ > 1.0f / RATE_RENDER) {
        awaitRender_ = true;
    }

    if (timeSinceUpdate_ > 1.0f / RATE_UPDATE) {
        timeSinceUpdate_ -= 1.0f / RATE_UPDATE;
        awaitUpdate_ = true;
    }
}

bool Engine::update() {
    if (awaitUpdate_) {
        awaitUpdate_ = false;
        engine_update();
    }

    if (awaitRender_) {
        awaitRender_ = false;
        engine_render();
        timeSinceFps_ += timeSinceRender_;
        framesSinceFps_++;
        if(timeSinceFps_ > 1) {
            timeSinceFps_ -= 1;
            fps = framesSinceFps_;
            framesSinceFps_ = 0;
        }
        timeSinceRender_ = 0;
        return true;
    }

    return false;
}