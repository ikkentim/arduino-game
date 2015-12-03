#include <stdlib.h>
#include "Random.h"
#include "Nunchuck.h"

unsigned int Random::seed_ = 0;

void Random::generate_seed(uint8_t ticks, Nunchuck *nunchuck) {
    //int is 16 bit
	//prime numbers for generation of the seed
    const unsigned int p1 = 45013;
    const unsigned int p2 = 34429;
    const unsigned int p3 = 54421;
    const unsigned int p4 = 27407;

    Vector3 accel = nunchuck->acceleration();
    float aX = accel.x,
            aY = accel.y,
            aZ = accel.z;

    unsigned int seed = (unsigned int) (
            (int) (aX * p1 +
                   aY * p2 +
                   aZ * p3 +
                   ticks * ticks) % p4);
	//Add the seed to the _seed value so that it overflows
    Random::seed_ += seed;
    srand(Random::seed_); //Set the rand seed.
}

int Random::rand_integer(const int &range_min, const int &range_max) {
    return (rand() + range_min) % range_max;
}

uint8_t Random::rand_uint8_t(const uint8_t &range_min, const uint8_t &range_max) {
    return (uint8_t)((rand() + (int) range_min) % (int) range_max);
}

float Random::rand_float(const float &range_min, const float &range_max) {
    float frand = (float) rand() / (float) RAND_MAX;
    float max = range_max - range_min;
    return frand * max + range_min;
}

int Random::get_seed() const {
    return Random::seed_;
}
