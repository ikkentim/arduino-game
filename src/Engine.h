#ifndef ARDUINOGAME_ENGINE_H
#define ARDUINOGAME_ENGINE_H

#include <TFT.h>
#include "Color.h"
#include "Nunchuck.h"
#include "ShapeRenderer.h"

class Engine {
public:
    Engine(Nunchuck *nunchuck, TFT *tft);
    void tick(float timeElapsed);
    bool update();
    Nunchuck *nunchuck;
    ShapeRenderer sr;
    TFT *tft;
protected:
    virtual void engine_update(float deltaTime) = 0;
    virtual void engine_render() = 0;
private:
    bool awaitRender_;
    bool awaitUpdate_;
    bool awaitDebug_;
    float timeSinceRender_;
    float timeSinceUpdate_;
    float timeSinceFps_;
    int fps_;
    int frames_;
    uint8_t debugCounter_;
    void display_free_ram();
};


#endif //ARDUINOGAME_ENGINE_H
