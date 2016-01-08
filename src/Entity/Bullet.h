#include "BaseEntity.h"
#ifndef ARDUINOGAME_BULLET_H
#define ARDUINOGAME_BULLET_H

class Game;
class TestLevel;
class Player;

class Bullet : public BaseEntity {
public:
    Bullet(Game *game, Level *level, Player *player);

	void update(const float& delta);
    void render();
    void collided(BaseEntity* other);
private:
	int old_position_x_;
	int old_position_y_;

};

#endif //ARDUINOGAME_BULLET_H
