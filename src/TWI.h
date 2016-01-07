#ifndef ARDUINOGAME_TWI_H
#define ARDUINOGAME_TWI_H

#include <stdint.h>

class TWI {
public:
    TWI();
    uint8_t start(uint8_t address, bool read);
    void startWait(uint8_t address, bool read);
    void stop();
    uint8_t read(bool sendAck);
    void write(uint8_t value);
};

#endif // ARDUINOGAME_TWI_H