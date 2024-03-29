#include <avr/interrupt.h>
#include <EEPROM.h>
#include "TFTScreen.h"
#include "Nunchuck.h"
#include "Game.h"

// include some header files of libraries used by various libraries.
// this triggers platform.io to load the packages they are a part of.

Game *game = 0;
TFTScreen *tft;
Nunchuck *nc;

void enableTimer2Interrupt() {
    // set the prescaler to 32 and enable the interrupt.
    TCCR2B = 0 << CS22 | 1 << CS21 | 1 << CS20;
    TIMSK2 |= 1 << TOIE2;

    // enable interrupts
    sei();
}

ISR(TIMER2_OVF_vect) {
    // if the game has been initialized, advance it's internal timers.
    if (game)
        game->tick((float) 1 / ((float) 16000000 / 256 / 32 / 1));
}


int main(void) {
//#define RESET_HIGHSCORE
#ifdef RESET_HIGHSCORE
    EEPROM.begin();
    EEPROM.put(2, 0);
    EEPROM.end();
#else
    // enable the timer 2 interrupt.
    enableTimer2Interrupt();

    // initialize the tft screen and clear it to it's initial color.
    tft = new TFTScreen();
    //tft->begin();
    //tft->led(100);
    tft->fill_screen(RGB(0, 0, 0));

    // initialize nunchuck
    nc = new Nunchuck();

    // create an instance of the game.
    game = new Game(nc, tft);

    // keep updating the game until the end of time (or the power is cut (or the arduino is broken)).
    for (; ;) {
        game->update();
    }
#endif
}

