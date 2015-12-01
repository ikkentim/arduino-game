#include <stdio.h>
#include <stdlib.h>
#include "TestLevel.h"
#include "../Entity/TestEntity.h"
#include "../ShapeRenderer.h"
#include <avr/pgmspace.h>

const int8_t playerShape[] PROGMEM = {
    -5, 7, 0, 0,
    -5, -7, 0, 0,
    -5, 7, 16, 0,
    -5, -7, 16, 0
};

ShapeRenderer sr;
float r = 0;
float xx = 100;
void TestLevel::render(MI0283QT9 *tft) {
    float oldr = r;
    float oldx = xx;
    r += game->nunchuck->joystick().x / 10;
    xx += game->nunchuck->joystick().y;

    sr.render(tft, (int8_t *)playerShape, 4, RGB(255,255,255), 60,(int)oldx , oldr, 60, (int)xx , r);
    //sr.render(tft, (int8_t *)playerShape, 4, RGB(255,255,255), 160,160 , oldr, 160, 160 , r);
}

TestLevel::TestLevel(Game *game) : Level(game) {
    testEntity_ = new TestEntity(game);
}

TestLevel::~TestLevel()
{
    delete testEntity_;
}
void TestLevel::update() {
    testEntity_->update(0.16f);
}

