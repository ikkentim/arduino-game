#ifndef ARDUINOGAME_RANDOM_H
#define ARDUINOGAME_RANDOM_H

#include <stdint.h>

class MenuLevel;
class Nunchuck;

class Random {
public:
    int rand_integer(const int& range_min, const int& range_max = RAND_MAX);
    uint8_t rand_uint8_t(const uint8_t& range_min, const uint8_t& range_max = 255);
    float rand_float(const float& range_min, const float& range_max = RAND_MAX);
    int get_seed() const;
private:
    //The seed for the random generator
    static unsigned int seed_;
protected:
    friend class MenuLevel;
    //Generate seed, use this method before calling any rand functions as this method calls srand().
    static void generate_seed(uint8_t ticks, Nunchuck* nunchuck);
};


#endif //ARDUINOGAME_RANDOM_H
