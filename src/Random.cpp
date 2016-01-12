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

    int seed =
            (int) (aX * p1 +
                   aY * p2 +
                   aZ * p3 +
                   ticks * ticks) % p4;
	//Add the seed to the _seed value so that it overflows
    Random::seed_ += (unsigned int)seed + rand();
    srand(Random::seed_); //Set the rand seed.
}