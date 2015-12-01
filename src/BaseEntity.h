#include "Vector2.h"
#include "Game.h"
#include "ShapeRenderer.h"

#ifndef ARDUINOGAME_BASEENTITY_H
#define ARDUINOGAME_BASEENTITY_H

//Base entity class, other entities inherit from this class.
class BaseEntity {
public:
    BaseEntity(Game *game) { game_ = game; }

    //Always make base classes' destructors virtual when they're meant to be manipulated polymorphically.
    virtual ~BaseEntity() { };

    //Updates this entity.
    virtual void update(float delta) = 0;

    //Render this entity.
    virtual void render(ShapeRenderer *renderer) = 0;

    //The position in the level
    Vector2 position;
    //The speed and direction of this object
    Vector2 velocity;
    //Rotation of the sprite
    float rotation;
    //Shape for this object
    //Shape* shape;
protected:
    Game *game_;
};

#endif //ARDUINOGAME_BASEENTITY_H
