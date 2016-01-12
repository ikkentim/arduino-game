#ifndef ARDUINOGAME_RANDOM_H
#define ARDUINOGAME_RANDOM_H

#include <stdlib.h>
#include <stdint.h>

class MenuLevel;
class Nunchuck;

class Random {
private:
    //The seed for the random generator
    static unsigned int seed_;
protected:
    friend class MenuLevel;

    //Generate seed, use this method before calling any rand functions as this method calls srand().
    static void generate_seed(uint8_t ticks, Nunchuck *nunchuck);
};

inline int rand_integer(const int& range_min, const int& range_max = RAND_MAX){
    return (rand() + range_min) % range_max;
}

inline uint8_t rand_uint8_t(const uint8_t& range_min, const uint8_t& range_max = 255){
    return (uint8_t)((rand() + (int)range_min) % (int)range_max);
}
inline float rand_float(const float& range_min, const float& range_max = RAND_MAX){
    float frand = (float)rand() / (float)RAND_MAX;
    float max = range_max - range_min;
    return frand * max + range_min;
}

#endif //ARDUINOGAME_RANDOM_H
