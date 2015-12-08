#include <stdio.h>
#include <stdlib.h>
#include "TestLevel.h"
#include "../Entity/TestEntity.h"
#include "../ShapeRenderer.h"
#include "../Asteroid.h"

float r = 0;
float xx = 100;

TestLevel::TestLevel(Game *game) : Level(game) {

//    testEntity_ = new TestEntity(game);
    player_ = new Player(game);
    testAsteroid_ = new Asteroid(game);

    addEntity(player_);
    addEntity(testAsteroid_);
}

TestLevel::~TestLevel()  {
}

void TestLevel::update(float deltaTime) {
//    testEntity_->update(deltaTime);
    player_->update(deltaTime);
    testAsteroid_->update(deltaTime);
}

void TestLevel::render() {
    player_->render();
    testAsteroid_->render();
}

