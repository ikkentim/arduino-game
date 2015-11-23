#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <SPI.h>
#include <digitalWriteFast.h>
#include <MI0283QT9.h>

#include "Nunchuck.h"
#include "Game.h"

Game *game = 0;

void enableInterrupt() {
    TCCR2B = 0x00;
    TCCR2A &= ~((1 << COM0A0) | (1 << COM0A1));
    TCCR2B = 1 << CS22 | 1 << CS21 | 0 << CS20;
    TIMSK2 |= 1 << TOIE2;

    sei();
}

ISR(TIMER2_OVF_vect) {
    if(game)
        game->tick((float)1 / 122);
}

int main(void) {
    MI0283QT9 tft;
    Nunchuck nc;

    init();
    enableInterrupt();

    nc.begin();

    tft.begin();
    tft.led(100);
    tft.fillScreen(RGB(255, 0, 0));

    game = new Game(&nc, &tft);

    for( ;;) {
        game->update();
    }
}

