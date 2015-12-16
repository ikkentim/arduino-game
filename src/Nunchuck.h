#ifndef ARDUINOGAME_NUNCHUCK_H
#define ARDUINOGAME_NUNCHUCK_H

#include "Vector3.h"
#include "Vector2.h"

class Nunchuck {
public:
    Nunchuck();
    // initializes the ports used by the device.
    bool begin();
    // pulls data from the device.
    void update();
    // gets the type of the device.
    uint8_t type();
    // gets the acceleration of the device. the components of the vector range from -1.0f to 1.0f.
    Vector3 acceleration();
    // gets the position of the joystick on the device. the components of the vector range from -1.0f to 1.0f.
    Vector2 joystick();
    // gets a value indicating whether the c button is being pressed.
    bool button_c();
    // gets a value indicating whether the z button is being pressed.
    bool button_z();
    // round the joystick from <0.1 to 0
    bool calibrate;
private:
    bool init();
    uint8_t clear_input();
    void send_request();
    bool receive_data();
    float range_from_10bits(uint8_t byte, uint8_t bits, uint16_t min, uint16_t max);
    float range_from_8bits(uint8_t byte, uint8_t min, uint8_t max);
    void wrap(Vector2 *vector);
    void wrap(Vector3 *vector);
    uint8_t type_; // 0 - disconnected, 1 - old, 2 - new
    uint8_t buffer_[8];

    Vector2 position_;
    Vector3 acceleration_;
    bool z_pressed_;
    bool c_pressed_;
};


#endif //ARDUINOGAME_NUNCHUCK_H
