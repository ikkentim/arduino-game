#ifndef ARDUINOGAME_LEVEL_H
#define ARDUINOGAME_LEVEL_H
#define MAX_ENTITY_COUNT 15

#include "../Game.h"
#include "../Entity/BaseEntity.h"

class Game;
class BaseEntity;

class Level {
public:
    Level(Game *game);
    virtual ~Level();
    virtual void update(float delta) = 0;
    virtual void render() = 0;
    void addEntity(BaseEntity *entity);
    void removeEntity(BaseEntity *entity);
    BaseEntity* entities[MAX_ENTITY_COUNT];
    int entityCount = 0;
protected:
    Game *game;
};


#endif //ARDUINOGAME_LEVEL_H
