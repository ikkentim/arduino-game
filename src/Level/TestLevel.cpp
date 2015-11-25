#include <stdio.h>
#include <stdlib.h>
#include "TestLevel.h"
#include "../Entity/TestEntity.h"
void TestLevel::render(MI0283QT9 *tft) {

}

TestLevel::TestLevel(Game *game) : Level(game) {
    testEntity_ = new TestEntity(game);
}

TestLevel::~TestLevel()
{
    delete testEntity_;
}
void TestLevel::update() {
    testEntity_->update(0.16f); //TODO: add delta time to Level::update
}

