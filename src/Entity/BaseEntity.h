#include "../Level/TestLevel.h"
#include "../Vector2.h"
#include "../Game.h"
#include "../ShapeRenderer.h"

#ifndef ARDUINOGAME_BASEENTITY_H
#define ARDUINOGAME_BASEENTITY_H

class TestLevel;
class Game;

typedef uint8_t EntityType;
#define TYPE_ASTEROID 0
#define TYPE_PLAYER 1
#define TYPE_BULLET 2
#define TYPE_POWERUP 3



//Base entity class, other entities inherit from this class.
class BaseEntity {
public:
    BaseEntity(Game *game, Level *level) :
        game_(game),
        level_(level) {
        rotation = 0;
        old_rotation = 0;
        old_draw_position_x = 0;
        old_draw_position_y = 0;
    }

    //Always make base classes' destructors virtual when they're meant to be manipulated polymorphically.
    virtual ~BaseEntity() { };

    //Updates this entity.
    virtual void update(const float& delta) = 0;

    //Render this entity.
    virtual void render() = 0;

    //The position in the level
    Vector2 position;

    //The speed and direction of this object
    Vector2 velocity;
    //Rotation of the sprite
    float rotation;
    float old_rotation;

    bool collision_check;
    uint8_t collision_radius;
    virtual void collided(BaseEntity* other) {};
    EntityType entity_type;
protected:
    int old_draw_position_x;
    int old_draw_position_y;
    Game *game_;
    Level *level_;
};

#endif //ARDUINOGAME_BASEENTITY_H
