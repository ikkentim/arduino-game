#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Nunchuck.h"

#define NC_ADDRESS          0x52
#define NC_REQUEST          0x00

#define NC1_INIT_REGISTER    0x40
#define NC1_INIT_DATA        0x00

#define NC2_INIT_REGISTER    0xf0
#define NC2_INIT_DATA        0x55

Nunchuck::Nunchuck() {
    type_ = 0;
    calibrate=true;
    // enable power on arduino A2/A3 pins
    DDRC |= _BV(PINC3) | _BV(PINC2);
    PORTC &= ~_BV(PINC2);
    PORTC |= _BV(PINC3);

    // enable the two wire interface.
    twi_ = new TWI();

    // give connected devices some time to boot.
    _delay_ms(50);

    // initialize the connected device.
    this->init();
}

bool Nunchuck::init() {
    if (!send_init(NC1_INIT_REGISTER, NC1_INIT_DATA)) return false;
    _delay_ms(5);

    if(!send_request()) {
        return false;}
    _delay_ms(5);

    if (read_byte() != 255) {
        type_ = 1;
    }
    else {
        if (!send_init(NC2_INIT_REGISTER, NC2_INIT_DATA)) return false;
        _delay_ms(5);

        if(!send_request()) return false;
        _delay_ms(5);

        if (read_byte() != 255) {
            type_ = 2;
        }
        else {
            return false;
        }
    }

    send_request();
    _delay_ms(5);

    return true;
}

void Nunchuck::update() {
    // if no device has been connected and the initialisation method failed, do not proceed with the update.
    if (type_ <= 0 && !init()) {
        return;}

    // attempt to store the received data to the buffer. if data can not be received, assume the device has been
    // disconnected and reset the type to 0.
    if (!receive_data()) {
        type_ = 0;
    }

    // handle last requests' data
    z_pressed_ = type_ && !((buffer_[5] >> 0) & 1);
    c_pressed_ = type_ && !((buffer_[5] >> 1) & 1);

    position_ = !type_ ? Vector2() : Vector2(
        range_from_8bits(buffer_[0], 0, 255),
        range_from_8bits(buffer_[1], 0, 255)
    );

    acceleration_ = !type_ ? Vector3() : Vector3(
        range_from_10bits(buffer_[2], (buffer_[5] >> 2) & 3, 0, 1023),
        range_from_10bits(buffer_[3], (buffer_[5] >> 4) & 3, 0, 1023),
        range_from_10bits(buffer_[4], (buffer_[5] >> 6) & 3, 0, 1023)
    );

    wrap(&position_);
    wrap(&acceleration_);

    // send a new request for data ahead for the next update.
    send_request();
}

bool Nunchuck::send_request() {
    // send a request byte to the device.
    if (twi_->start(NC_ADDRESS, false)) return false;
    twi_->write(NC_REQUEST);
    twi_->stop();

    return true;
}

bool Nunchuck::receive_data() {
    twi_->startWait(NC_ADDRESS, true);

    for (uint8_t i = 0; i < 6; i++) {
        uint8_t raw = twi_->read(i != 5);

        // write the read value to the buffer. if we're dealing with an old nunchuck, decode the value first.
        buffer_[i] = type_ == 1 ? ((raw ^ 0x17) + 0x17) : raw;
    }

    twi_->stop();

    // request 6 bytes from the device to write to the buffer.
    if(!send_request()) return false;
    _delay_us(500);

    return true;
}

Vector3 Nunchuck::acceleration() {
    // if no device has been connected, return an empty vector. otherwise, return a vector filled with acceleration
    // data.
    return acceleration_;
}

Vector2 Nunchuck::joystick() {
    // if no device has been connected, return an empty vector. otherwise, return a vector filled with joystick data.
    return position_;
}

bool Nunchuck::button_z() {
    // return a value indicating whether any device has been connected and the z button has been pressed.
    return z_pressed_;
}

bool Nunchuck::button_c() {
    // return a value indicating whether any device has been connected and the c button has been pressed.
    return c_pressed_;
}

float Nunchuck::range_from_10bits(uint8_t byte, uint8_t bits, uint16_t min, uint16_t max) {
    // return a number between -1 and 1 based on the specified 10 bit number and range.
    uint16_t value = (byte << 2) | (bits & 3);
    value -= min;
    max -= min;
    return ((float) value / max) * 2 - 1;
}

float Nunchuck::range_from_8bits(uint8_t byte, uint8_t min, uint8_t max) {
    // return a number between -1 and 1 based on the specified 8 bit number and range.
    byte -= min;
    max -= min;
    return ((float) byte / max) * 2 - 1;
}

uint8_t Nunchuck::type() {
    return type_;
}

void Nunchuck::wrap(Vector2 *vector) {
    if(!calibrate) return;
    if (fabs(vector->x) < 0.1f) {
        vector->x = 0;
    }
    if (fabs(vector->y) < 0.1f) {
        vector->y = 0;
    }
}

void Nunchuck::wrap(Vector3 *vector) {
    if(!calibrate) return;
    if (fabs(vector->x) < 0.1f) {
        vector->x = 0;
    }
    if (fabs(vector->y) < 0.1f) {
        vector->y = 0;
    }
    if (fabs(vector->z) < 0.1f) {
        vector->z = 0;
    }
}

bool Nunchuck::send_init(uint8_t a, uint8_t b) {
    if (twi_->start(NC_ADDRESS, false)) {
        return false;
    }

    twi_->write(a);
    twi_->write(b);
    twi_->stop();

    return true;
}

uint8_t Nunchuck::read_byte() {
    if (twi_->start(NC_ADDRESS, true)) return 255;
    uint8_t value = twi_->read(false);
    twi_->stop();

    return value;
}