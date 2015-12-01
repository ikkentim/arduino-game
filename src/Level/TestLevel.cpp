#include <stdio.h>
#include <stdlib.h>
#include "TestLevel.h"
#include "../Entity/TestEntity.h"
#include "../ShapeRenderer.h"
#include <avr/pgmspace.h>

const int8_t playerShape[] PROGMEM = {
    -5, 6, 0, 0,
    -5, -6, 0, 0,
    -5, 6, 15, 0,
    -5, -6, 15, 0
};

ShapeRenderer sr;
float r = 0;
float xx = 100;
void TestLevel::render(TFT *tft) {
    float oldr = r;
    float oldx = xx;
    r += game->nunchuck->joystick().x / 10;
    xx += game->nunchuck->joystick().y;

    sr.render(tft, (int8_t *)playerShape, 4, RGB(255,255,255), 60,(int)oldx , oldr, 60, (int)xx , r);
}

TestLevel::TestLevel(Game *game) : Level(game) {
    testEntity_ = new TestEntity(game);
}

TestLevel::~TestLevel()
{
    delete testEntity_;
}
void TestLevel::update(float deltaTime) {
    testEntity_->update(deltaTime);
}

