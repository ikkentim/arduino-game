#ifndef ARDUINOGAME_NUNCHUCK_H
#define ARDUINOGAME_NUNCHUCK_H

#include "Vector3.h"
#include "Vector2.h"
#include "TWI.h"

class Nunchuck {
public:
    Nunchuck();
    // pulls data from the device.
    void update();
    // gets the type of the device.
    inline uint8_t type() { return type_; }
    // gets the acceleration of the device. the components of the vector range from -1.0f to 1.0f.
    inline Vector3 acceleration() { return acceleration_;}
    // gets the position of the joystick on the device. the components of the vector range from -1.0f to 1.0f.
    inline Vector2 joystick() { return position_; }
    // gets a value indicating whether the c button is being pressed.
    inline bool button_c() { return c_pressed_; }
    // gets a value indicating whether the z button is being pressed.
    inline bool button_z() { return z_pressed_; }

    bool calibrate;
private:
    bool init();
    bool send_request();
    bool send_init(uint8_t a, uint8_t b);
    uint8_t read_byte();
    bool receive_data();
    float range_from_10bits(uint8_t byte, uint8_t bits, uint16_t min, uint16_t max);
    float range_from_8bits(uint8_t byte, uint8_t min, uint8_t max);
    void wrap(Vector2 *vector);
    void wrap(Vector3 *vector);
    uint8_t type_; // 0 - disconnected, 1 - old, 2 - new
    uint8_t buffer_[8];

    TWI *twi_;
    Vector2 position_;
    Vector3 acceleration_;
    bool z_pressed_;
    bool c_pressed_;
};


#endif //ARDUINOGAME_NUNCHUCK_H