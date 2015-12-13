#include "../Level/TestLevel.h"
#include "../Vector2.h"
#include "../Game.h"
#include "../ShapeRenderer.h"

#ifndef ARDUINOGAME_BASEENTITY_H
#define ARDUINOGAME_BASEENTITY_H

class TestLevel;
class Game;

//Base entity class, other entities inherit from this class.
class BaseEntity {
public:
    BaseEntity(Game *game, TestLevel *level) :
        game_(game),
        level_(level) {
        rotation = 0;
        old_rotation = 0;
    }

    //Always make base classes' destructors virtual when they're meant to be manipulated polymorphically.
    virtual ~BaseEntity() { };

    //Updates this entity.
    virtual void update(const float& delta) = 0;

    //Render this entity.
    virtual void render() = 0;

    //The position in the level
    Vector2 position;
	int old_position_x;
	int old_position_y;

    //The speed and direction of this object
    Vector2 velocity;
    //Rotation of the sprite
    float rotation;
    float old_rotation;
    //Shape for this object
    //Shape* shape;
    bool collision_check;
    uint8_t collision_radius;
    virtual void collided(BaseEntity* other) = 0;
protected:
    Game *game_;
    TestLevel *level_;
};

#endif //ARDUINOGAME_BASEENTITY_H
