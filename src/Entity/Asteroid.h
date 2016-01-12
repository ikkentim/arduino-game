#ifndef ARDUINOGAME_ASTERIOID_H
#define ARDUINOGAME_ASTERIOID_H

#include "BaseEntity.h"
#include "PowerUp.h"

class Asteroid : public BaseEntity {

public:
	Asteroid(Game *game, Level *level, PowerUp* powerUp, const uint8_t& max_speed = 90, const uint8_t& min_speed = 30);
	void update(const float& delta);
    void render();
    void reset(bool undraw = true);
    uint8_t max_speed;
	uint8_t min_speed;


private:
	PowerUp* powerUp_;
	uint8_t shape_;
	float scale_;
};


#endif //ARDUINOGAME_ASTERIOID_H
