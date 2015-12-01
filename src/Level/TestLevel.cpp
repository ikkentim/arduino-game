#include <stdio.h>
#include <stdlib.h>
#include "TestLevel.h"
#include "../Entity/TestEntity.h"
#include "../ShapeRenderer.h"

float r = 0;
float xx = 100;

TestLevel::TestLevel(Game *game) : Level(game) {
//    testEntity_ = new TestEntity(game);
    player_ = new Player(game);
}

TestLevel::~TestLevel()
{
//    delete testEntity_;
}

void TestLevel::update(float deltaTime) {
//    testEntity_->update(deltaTime);
    player_->update(deltaTime);
}

void TestLevel::render(TFT *tft) {
    player_->render();
}

