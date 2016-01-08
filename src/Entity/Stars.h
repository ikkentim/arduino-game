#ifndef ARDUINOGAME_STARS_H
#define ARDUINOGAME_STARS_H

#include "BaseEntity.h"
#include "../Color.h"
class Game;
class TestLevel;

#define MAX_STAR_COUNT 10
#define RED_STAR 0
#define YELLOW_STAR 1
#define BLUE_STAR 2
#define MAX_OFFSET 50

typedef struct {
    float x;
    float y;
    int8_t offset;
    uint8_t brightness;
    uint8_t type;
} Star;

class Stars : public BaseEntity
{
public:
    Stars(Game *game, TestLevel *level);
    ~Stars();
    void update(const float& delta);
    void render();
    void collided(BaseEntity* other);
private:
    Star* stars_[MAX_STAR_COUNT];
    void reset_star(Star* star);
};

#endif //ARDUINOGAME_STARS_H
