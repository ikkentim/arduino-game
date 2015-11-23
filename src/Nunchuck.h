#ifndef ARDUINOGAME_NUNCHUCK_H
#define ARDUINOGAME_NUNCHUCK_H

#include "Vector3.h"
#include "Vector2.h"

class Nunchuck {
public:
    void begin();
    void update();
    Vector3 acceleration();
    Vector2 joystick();
    bool button_c();
    bool button_z();
private:
    float range_from_10bits(uint8_t byte, uint8_t bits, uint16_t min, uint16_t max);
    float range_from_8bits(uint8_t byte, uint8_t min, uint8_t max);
    uint8_t buffer_[8];
};


#endif //ARDUINOGAME_NUNCHUCK_H
