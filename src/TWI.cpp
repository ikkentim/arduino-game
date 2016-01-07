#include "TWI.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#define STATUS_MASK 0xF8
#define STATUS_START 0x08
#define STATUS_RSTART 0x10
#define STATUS_SLAW_ACK 0x18
#define STATUS_SLAW_NACK 0x20
#define STATUS_W_ACK 0x28
#define STATUS_W_NACK 0x30
#define STATUS_SLAR_ACK 0x40
#define STATUS_SLAR_NACK 0x48
#define STATUS_R_ACK 0x50
#define STATUS_R_NACK 0x58

#define TWI_INT		0b10000000 // 1 << TWINT
#define TWI_ACK		0b01000000 // 1 << TWEA
#define TWI_START	0b00100000 // 1 << TWSTA
#define TWI_STOP	0b00010000 // 1 << TWSTO
#define TWI_WRCOL	0b00001000 // 1 << TWWC
#define TWI_ENABLE	0b00000100 // 1 << TWEN
#define TWI_INTEN	0b00000001 // 1 << TWIE

#define TWI_PRESCALE 0b00 // 1 << TWSP1 | 1 << TWSP0, prescaler 1

#define TWI_FREQ 300000L //300 khz

char * b2bs(uint8_t c, char * bin);

void initTWI()
{
    TWSR = TWI_PRESCALE;
    TWBR = ((F_CPU / TWI_FREQ) - 16) / 2; // set TWI freq
}


void stopTransmition()
{
    TWCR = TWI_ENABLE | TWI_STOP | TWI_INT;
    while( TWCR & TWI_STOP );
}

uint8_t isStatus(uint8_t code)
{
    uint8_t status = TWSR & 0xF8;

    return code == status;
}

bool waitForFlag()
{
    uint16_t ticks = 0;
    while((~TWCR & TWI_INT)){if( ticks++ >1000) return false;}

    return true;
}

void writeByte(uint8_t b)
{
    TWDR = b;
    TWCR = TWI_ENABLE | TWI_INT; //clear interrupt flag
    waitForFlag();
}

uint8_t readByte( bool ack )
{
    TWCR = TWI_ENABLE | TWI_INT | (ack ? TWI_ACK : 0);
    if(!waitForFlag())
        return 0;
    return TWDR;
}

uint8_t startTransmition(uint8_t address, bool read)
{
    TWCR = TWI_START | TWI_INT | TWI_ENABLE;
    waitForFlag();

    if( !(isStatus(STATUS_START) || isStatus(STATUS_RSTART)) )
    {
        //Usart.writeln("Starting failed");
        return 1;
    }

    writeByte(address << 1 | (read ? 1 : 0)); // slave + write (0) or read (1)

    if( !(isStatus(STATUS_SLAW_ACK) || isStatus(STATUS_SLAR_ACK)) )
    {
        //Usart.writeln("error writing address");
        return 1;
    }

    return 0;
}

void startWaitTransmition(uint8_t address, bool read)
{
    for(;;)
    {
        TWCR = TWI_START | TWI_INT | TWI_ENABLE;
        waitForFlag();

        if( !(isStatus(STATUS_START) || isStatus(STATUS_RSTART)) )
        {
            //Usart.writeln("Starting failed");
            continue;
        }

        writeByte(address << 1 | (read ? 1 : 0)); // slave + write (0) or read (1)

        if( !(isStatus(STATUS_SLAW_ACK) || isStatus(STATUS_SLAR_ACK)) )
        {
            //Usart.writeln("stopping");
            stopTransmition();
            continue;
        }
        break;
    }
}
TWI::TWI() {
    initTWI();
}

uint8_t TWI::start(uint8_t address, bool read) {
    return startTransmition(address, read);
}

void TWI::stop() {
    stopTransmition();
}

uint8_t TWI::read(bool sendAck) {
    return readByte(sendAck);
}

void TWI::write(uint8_t value) {
    writeByte(value);
}

void TWI::startWait(uint8_t address, bool read) {
    startWaitTransmition(address, read);
}