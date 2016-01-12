#include "TWI.h"

#include <avr/io.h>

#define STATUS_START 0x08
#define STATUS_RSTART 0x10
#define STATUS_SLAW_ACK 0x18
#define STATUS_SLAR_ACK 0x40

#define TWI_PRESCALE 0x00

#define TWI_FREQ 300000L //300 khz

TWI::TWI() {
    TWSR = TWI_PRESCALE;
    TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
}

uint8_t TWI::start(uint8_t address, bool read) {
    TWCR = _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);
    waitForFlag();

    if (!(isStatus(STATUS_START) || isStatus(STATUS_RSTART))) {
        return 1;
    }

    write(address << 1 | (read ? 1 : 0));

    if (!(isStatus(STATUS_SLAW_ACK) || isStatus(STATUS_SLAR_ACK))) {
        return 1;
    }

    return 0;
}

void TWI::stop() {
    TWCR = _BV(TWEN) | _BV(TWSTO) | _BV(TWINT);
    while (TWCR & _BV(TWSTO));
}

uint8_t TWI::read(bool sendAck) {
    TWCR = _BV(TWEN) | _BV(TWINT) | (sendAck ? _BV(TWEA) : (uint8_t)0);
    if (!waitForFlag())
        return 0;
    return TWDR;
}

void TWI::write(uint8_t value) {
    TWDR = value;
    TWCR = _BV(TWEN) | _BV(TWINT); //clear interrupt flag
    waitForFlag();
}

void TWI::startWait(uint8_t address, bool read) {
    for (; ;) {
        TWCR = _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);
        waitForFlag();

        if (!(isStatus(STATUS_START) || isStatus(STATUS_RSTART))) {
            continue;
        }

        write(address << 1 | (read ? 1 : 0)); // slave + write (0) or read (1)

        if (!(isStatus(STATUS_SLAW_ACK) || isStatus(STATUS_SLAR_ACK))) {
            stop();
            continue;
        }
        break;
    }
}

bool TWI::waitForFlag() {
    uint16_t ticks = 0;
    while ((~TWCR & _BV(TWINT))) if (ticks++ > 1000) return false;
    return true;
}

bool TWI::isStatus(uint8_t code) {
    uint8_t status = TWSR & 0xF8;
    return code == status;
}
