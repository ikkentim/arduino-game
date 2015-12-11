#ifndef ARDUINOGAME_ASTERIOID_H
#define ARDUINOGAME_ASTERIOID_H

#include "BaseEntity.h"

class Asteroid : public BaseEntity {

public:
	Asteroid(Game *game, TestLevel *level, const uint8_t& max_speed = 50, const uint8_t& min_speed = 10);
	void update(const float& delta);
    void render();
    void collided(BaseEntity* other);
    void reset();
    bool destroyed;

    uint8_t max_speed;
	uint8_t min_speed;


};


#endif //ARDUINOGAME_ASTERIOID_H
