#include "Vector2.h"
#include "Game.h"
#include "ShapeRenderer.h"
#include "Level/TestLevel.h"

#ifndef ARDUINOGAME_BASEENTITY_H
#define ARDUINOGAME_BASEENTITY_H

class TestLevel;
//Base entity class, other entities inherit from this class.
class BaseEntity {
public:
    BaseEntity(Game *game, TestLevel *level) :
        game_(game),
        level_(level) {

    }

    //Always make base classes' destructors virtual when they're meant to be manipulated polymorphically.
    virtual ~BaseEntity() { };

    //Updates this entity.
    virtual void update(float delta) = 0;

    //Render this entity.
    virtual void render() = 0;

    //The position in the level
    Vector2 position;
    Vector2 old_position;
    //The speed and direction of this object
    Vector2 velocity;
    //Rotation of the sprite
    float rotation = 0;
    float old_rotation = 0;
    //Shape for this object
    //Shape* shape;
protected:
    Game *game_;
    TestLevel *level_;
};

#endif //ARDUINOGAME_BASEENTITY_H
