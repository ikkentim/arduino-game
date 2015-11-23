#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>
#include "Nunchuck.h"

#define NC_VERSION          1

#define NC_ADDRESS          0x52
#define NC_REQUEST          0x00

#if NC_VERSION == 1
#define NC_INIT_REGISTER    0x40
#define NC_INIT_DATA        0x00
#define NC_IS_ENCODED       1
#else
#define NC_INIT_REGISTER    0xf0
#define NC_INIT_DATA        0x55
#define NC_IS_ENCODED       0
#endif

void Nunchuck::begin() {
    // enable power on arduino A2/A3 pins
    DDRC |= _BV(PINC3) | _BV(PINC2);
    PORTC &= ~_BV(PINC2);
    PORTC |= _BV(PINC3);
    _delay_ms(100);

    Wire.begin();
    Wire.beginTransmission(NC_ADDRESS);
    Wire.write((uint8_t) NC_INIT_REGISTER);
    Wire.write((uint8_t) NC_INIT_DATA);
    Wire.endTransmission();
}

void Nunchuck::update() {

    Wire.requestFrom(NC_ADDRESS, 6);
    uint8_t i = 0;
    for (; i < 6 && Wire.available(); i++) {
        uint8_t raw = Wire.read();
//#if NC_IS_ENCODED == 1
        buffer_[i] = (raw ^ 0x17) + 0x17;
//#else
//        buffer_[i] = raw;
//#endif
    }

    Wire.beginTransmission(NC_ADDRESS);
    Wire.write((uint8_t) NC_REQUEST);
    Wire.endTransmission();

    if (i != 6) {
        while (1);
    }
}

Vector3 Nunchuck::acceleration() {
    return Vector3(
            range_from_10bits(buffer_[2], (buffer_[5] >> 2) & 3, 0, 1023),
            range_from_10bits(buffer_[3], (buffer_[5] >> 4) & 3, 0, 1023),
            range_from_10bits(buffer_[4], (buffer_[5] >> 6) & 3, 0, 1023)
    );
}

Vector2 Nunchuck::joystick() {
    return Vector2(
            range_from_8bits(buffer_[0], 0, 255),
            range_from_8bits(buffer_[1], 0, 255)
    );
}

bool Nunchuck::button_z() {
    return !((buffer_[5] >> 0) & 1);
}

bool Nunchuck::button_c() {
    return !((buffer_[5] >> 1) & 1);
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
