#ifndef ARDUINOGAME_NUNCHUCK_H
#define ARDUINOGAME_NUNCHUCK_H

#include "Vector3.h"
#include "Vector2.h"

class Nunchuck {
public:
    Nunchuck();
    bool begin();
    void update();
    uint8_t type();
    Vector3 acceleration();
    Vector2 joystick();
    bool button_c();
    bool button_z();
private:
    bool init();
    uint8_t clear_input();
    void send_request();
    bool retrieve_data();
    float range_from_10bits(uint8_t byte, uint8_t bits, uint16_t min, uint16_t max);
    float range_from_8bits(uint8_t byte, uint8_t min, uint8_t max);
    uint8_t type_; // 0 - disconnected, 1 - old, 2 - new
    uint8_t buffer_[8];
};


#endif //ARDUINOGAME_NUNCHUCK_H
