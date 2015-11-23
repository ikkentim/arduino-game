#ifndef ARDUINOGAME_ENGINE_H
#define ARDUINOGAME_ENGINE_H

#include <MI0283QT9.h>

#include "Color.h"
#include "Nunchuck.h"

class Engine {
public:
    Engine(Nunchuck *nunchuck, MI0283QT9 *tft);
    void tick(float timeElapsed);
    bool update();
protected:
    virtual void engine_update() = 0;
    virtual void engine_render() = 0;
    int fps;
    Nunchuck *nunchuck;
    MI0283QT9 *tft;
private:
    bool awaitRender_;
    bool awaitUpdate_;
    float timeSinceRender_;
    float timeSinceUpdate_;
    float timeSinceFps_;
    uint8_t framesSinceFps_;
};


#endif //ARDUINOGAME_ENGINE_H
