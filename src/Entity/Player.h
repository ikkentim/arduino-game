#ifndef ARDUINOGAME_PLAYER_H
#define ARDUINOGAME_PLAYER_H


#include "BaseEntity.h"
#include "../Game.h"

class Bullet;

class Player : public BaseEntity {

public:
    Player(Game *game, TestLevel *level);

	void update(const float& delta);
    void render();
    void collided(BaseEntity* other);
    void set_level(Level *level);

	bool has_powerup;
	int old_position_x_;
	int old_position_y_;
private:
    float acceleration_ = 70;
    float deceleration_ = 0.90f;
    float max_speed_ = 200;
    float rotation_speed_ = 3;
    float firing_cooldown_ = 0;

	uint8_t powerup_frame_;
    bool dead_;
};


#endif //ARDUINOGAME_PLAYER_H
