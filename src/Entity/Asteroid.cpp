#include "Asteroid.h"
#include "../Random.h"
#include <avr/pgmspace.h>

const int8_t shape1[] PROGMEM = {
    -15,  0, -1, -3,
     -1, -3,  0,-15,
      0,-15, 10,-10,
     10,-10, 15,  0,
     15,  0, 12, 11,
     12, 11,  0, 15,
      0, 15,-10, 10,
    -10, 10,-15,  0//8
};

const int8_t shape2[] PROGMEM = {
     -9,-15,  3,-15,
      3,-15, 15, -9,
     15, -9, 15, -3,
     15, -3,  0,  0,
      0,  0, 15,  9,
     15,  9,  3, 15,
      3, 15,  0, 12,
      0, 12, -9, 15,
     -9, 15,-15,  6,
     -15, 6, -15,-6,
     -15, -6,-3, -6,
     -3, -6, -9,-15//12
};

const int8_t shape3[] PROGMEM = {
	-6, -12, 0, -6,
	0, -6, 6, -12,
	6, -12, 15, -6,
	15, -6, 9, -3,
	9, -3, 15, 3,
	15, 3, 9, 12,
	9, 12, 0, 9,
	0, 9, -3, 12,
	-3, 12, -12, 9,
	-12, 9, -9, 3,
	-9, 2, -12, -6,
	-12, -6, -6, -12//12
};

void Asteroid::update(const float& delta) {
    position += velocity * delta;
	float range = collision_radius * 4;
	if (!level_->viewport.is_in_range(position,range))
	{
		reset();
	} 
}

void Asteroid::render() {
	
    Vector2 draw_position = position - level_->viewport.position();
	int8_t* shape;
	uint8_t lines = 12;
	switch (shape_)
	{
	case 0:
		shape = (int8_t *)shape1;
		lines = 8;
		break;
	case 1:
		shape = (int8_t *)shape2;
		break;
	default:
		shape = (int8_t *)shape3;
		break;
	}
		
	
	game_->sr.render(game_->tft, shape, lines, RGB(255, 255, 255),
                     old_position_x, old_position_y, old_rotation,
					 (int)draw_position.x, (int)draw_position.y, rotation, scale_);
	
    old_rotation = rotation;
	old_position_x = (int)draw_position.x;
	old_position_y = (int)draw_position.y;

}

Asteroid::Asteroid(Game *game, Level *level,
					const uint8_t& max_speed,
					const uint8_t& min_speed
                  ) : BaseEntity(game, level) {
    entity_type = TYPE_ASTEROID;
    collision_check = false;
    collision_radius = 16;
    this->min_speed = min_speed;
    this->max_speed = max_speed;
    reset(false);
}

void Asteroid::reset(bool undraw) {
	if(undraw) {
		Vector2 draw_position = position - level_->viewport.position();
		int8_t* shape;
		uint8_t lines = 12;
		switch (shape_)
		{
			case 0:
				shape = (int8_t *)shape1;
				lines = 8;
				break;
			case 1:
				shape = (int8_t *)shape2;
				break;
			default:
				shape = (int8_t *)shape3;
				break;
		}

		game_->sr.render(game_->tft, shape, lines, RGB(0, 0, 0),
						 old_position_x, old_position_y, old_rotation,
						 (int)draw_position.x, (int)draw_position.y, rotation, scale_);
	}

	shape_ = rand_uint8_t(0, 3);
	scale_ = rand_float(0.5f, 1.0f);
	collision_radius = (uint8_t)(16 * scale_);
    Vector2 viewport_position = level_->viewport.position();
    Vector2 viewport_size = level_->viewport.size();
	rotation = rand_float(0.0f, 6.28f);
    position = Vector2(
            rand_float(-10.0f, 10.0f),
            rand_float(-10.0f, 10.0f)
    );
    position.normalize();

	position = (viewport_position + viewport_size / 2) + position * viewport_size.length()/2;

    velocity = Vector2(
            rand_float(-1.0f, 1.0f),
            rand_float(-1.0f, 1.0f)
    );

	Vector2 target = (viewport_position + viewport_size / 2) - position;
	target.normalize();
    velocity.normalize();
	velocity = target + velocity * 0.5f;

    velocity.normalize();
    velocity = velocity * rand_float(min_speed, max_speed);

	float multiplier = (float)(game_->score->get_score() - 20) / 50.0f;

	if(multiplier > 1)
	{
		if(multiplier > 5) multiplier = 5.0f;
		velocity = velocity * multiplier;
	}
}

void Asteroid::collided(BaseEntity *other) {

}
