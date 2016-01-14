#ifndef ARDUINOGAME_ENGINE_H
#define ARDUINOGAME_ENGINE_H

#include "Nunchuck.h"
#include "ShapeRenderer.h"

class Engine {
public:
    Engine(Nunchuck *nunchuck, TFTScreen *tft);
    void tick(float timeElapsed);
    bool update();
    Nunchuck *nunchuck;
    ShapeRenderer sr;
    TFTScreen *tft;
protected:
    virtual void engine_update(float deltaTime) = 0;
    virtual void collision_detection() = 0;
    virtual void engine_render() = 0;
private:
    bool awaitRender_;
    bool awaitUpdate_;
    float timeSinceRender_;
    float timeSinceUpdate_;
};


#endif //ARDUINOGAME_ENGINE_H
