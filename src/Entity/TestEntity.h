//
// Created by Roelof on 11/25/2015.
//

#include "BaseEntity.h"

#ifndef ARDUINOGAME_TESTENTITY_H
#define ARDUINOGAME_TESTENTITY_H
class Game;
class ShapeRenderer;

class TestEntity : public BaseEntity
{
public:
    TestEntity(Game* game);

    virtual void update(float delta);
    virtual void render(ShapeRenderer* renderer);

};
#endif //ARDUINOGAME_TESTENTITY_H
