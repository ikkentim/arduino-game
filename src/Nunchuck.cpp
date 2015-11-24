#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>
#include "Nunchuck.h"

#define NC_ADDRESS          0x52
#define NC_REQUEST          0x00

#define NC1_INIT_REGISTER    0x40
#define NC1_INIT_DATA        0x00

#define NC2_INIT_REGISTER    0xf0
#define NC2_INIT_DATA        0x55

Nunchuck::Nunchuck() {
    type_ = 0;
}

bool Nunchuck::begin() {
    // enable power on arduino A2/A3 pins
    DDRC |= _BV(PINC3) | _BV(PINC2);
    PORTC &= ~_BV(PINC2);
    PORTC |= _BV(PINC3);
    _delay_ms(50);

    Wire.begin();

    return init();
}

bool Nunchuck::init() {
    // request id
    Wire.beginTransmission(NC_ADDRESS);
    Wire.write((uint8_t)0xFA);
    Wire.endTransmission();

    type_ = clear_input() < 6 ? 1 : 2;
    // initialize registers
    Wire.beginTransmission(NC_ADDRESS);
    Wire.write((uint8_t) NC1_INIT_REGISTER);
    Wire.write((uint8_t) NC1_INIT_DATA);
    Wire.endTransmission();

    Wire.beginTransmission(NC_ADDRESS);
    Wire.write((uint8_t) NC2_INIT_REGISTER);
    Wire.write((uint8_t) NC2_INIT_DATA);
    Wire.endTransmission();

    clear_input();

    send_request();
    if(!retrieve_data()) {
        type_ = 0;
    }
    send_request();

    return true;
}

void Nunchuck::update() {
    if(type_ <= 0 && !init()) return;

    if(!retrieve_data()) {
        type_ = 0;
    }

    send_request();
}

void Nunchuck::send_request() {
    Wire.beginTransmission(NC_ADDRESS);
    Wire.write((uint8_t) NC_REQUEST);
    Wire.endTransmission();
}

bool Nunchuck::retrieve_data() {
    Wire.requestFrom(NC_ADDRESS, 6);

    uint8_t i = 0;
    for (; i < 6 && Wire.available(); i++) {
        uint8_t raw = (uint8_t) Wire.read();
        buffer_[i] = type_ == 1 ? ((raw ^ 0x17) + 0x17) : raw;
    }

    clear_input();
    return i == 6;
}

Vector3 Nunchuck::acceleration() {
    return !type_ ? Vector3() : Vector3(
            range_from_10bits(buffer_[2], (buffer_[5] >> 2) & 3, 0, 1023),
            range_from_10bits(buffer_[3], (buffer_[5] >> 4) & 3, 0, 1023),
            range_from_10bits(buffer_[4], (buffer_[5] >> 6) & 3, 0, 1023)
    );
}

Vector2 Nunchuck::joystick() {
    return !type_ ? Vector2() : Vector2(
            range_from_8bits(buffer_[0], 0, 255),
            range_from_8bits(buffer_[1], 0, 255)
    );
}

bool Nunchuck::button_z() {
    return type_ && !((buffer_[5] >> 0) & 1);
}

bool Nunchuck::button_c() {
    return type_ && !((buffer_[5] >> 1) & 1);
}

float Nunchuck::range_from_10bits(uint8_t byte, uint8_t bits, uint16_t min, uint16_t max) {
    uint16_t value = (byte << 2) | (bits & 3);
    value -= min;
    max -= min;
    return ((float) value / max) * 2 - 1;
}

float Nunchuck::range_from_8bits(uint8_t byte, uint8_t min, uint8_t max) {
    byte -= min;
    max -= min;
    return ((float) byte / max) * 2 - 1;
}

uint8_t Nunchuck::type() {
    return type_;
}

uint8_t Nunchuck::clear_input() {
    uint8_t count;

    Wire.requestFrom(NC_ADDRESS, 128);
    for(count = 0; Wire.available();count++)
        Wire.read();

    return count;
}
