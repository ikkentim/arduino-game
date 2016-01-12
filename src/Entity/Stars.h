#ifndef ARDUINOGAME_STARS_H
#define ARDUINOGAME_STARS_H

#include "BaseEntity.h"
#include "../Color.h"
class Game;
class TestLevel;

#define MAX_STAR_COUNT 10
#define MAX_OFFSET 100

typedef struct {
    Vector2 position;
    int8_t offset;
    uint8_t brightness;
} Star;

class Stars : public BaseEntity
{
public:
    Stars(Game *game, TestLevel *level, Player *player);
    ~Stars();
    void update(const float& delta);
    void render();
private:
    Star* stars_[MAX_STAR_COUNT];
    Player* player_;
    void reset_star(Star* star);
    Vector2 stars_position_offset_;
};

#endif //ARDUINOGAME_STARS_H
