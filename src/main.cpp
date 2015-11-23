#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <SPI.h>
#include <digitalWriteFast.h>
#include <MI0283QT9.h>
#include "Nunchuck.h"

#ifndef LCD_WIDTH
# define LCD_WIDTH      320
# define LCD_HEIGHT     240
#endif

int
        lastx = 0,
        lasty = 0,
        lastjx = 0,
        lastjy = 0;

volatile unsigned int seconds = 0;

MI0283QT9 lcd;
Nunchuck nc;

void enableInterrupt() {
    TCCR2B = 0x00;
    TCCR2A &= ~((1 << COM0A0) | (1 << COM0A1));
    TCCR2B = 1 << CS22 | 1 << CS21 | 0 << CS20;
    TIMSK2 |= 1 << TOIE2;

    sei();
}

ISR(TIMER2_OVF_vect) {
    static uint8_t counter = 0;
    counter++;
    if (counter == 122) {
        seconds++;
        counter = 0;
    }
}

int main(void) {
    init();
    enableInterrupt();

    nc.begin();

    lcd.begin();
    lcd.led(100);

    lcd.fillScreen(RGB(255, 0, 0));

    while (true) {
        char buf[64];

        nc.update();

        sprintf(buf, "Time: %d, Z: %d, C: %d ", seconds, nc.button_z(), nc.button_c());

        lcd.drawText(5, 5, buf, RGB(255, 255, 255), RGB(255, 0, 0), 1);

        Vector3 a = nc.acceleration();
        sprintf(buf, "acc:(%d, %d, %d)         ", (int) (a.x * 1000), (int) (a.y * 1000), (int) (a.z * 1000));
        lcd.drawText(5, 15, buf, RGB(255, 255, 255), RGB(255, 0, 0), 1);

        Vector2 j = nc.joystick();
        sprintf(buf, "joy:(%d, %d)      ", (int) (j.x * 1000), (int) (j.y * 1000));
        lcd.drawText(5, 25, buf, RGB(255, 255, 255), RGB(255, 0, 0), 1);

        lcd.fillCircle(lastx, LCD_HEIGHT - lasty, 5, RGB(255, 0, 0));
        lcd.fillCircle(lastjx, LCD_HEIGHT - lastjy, 3, RGB(255, 0, 0));

        int x = (int) ((a.x + 1) / 2 * LCD_WIDTH);
        int y = (int) ((a.y + 1) / 2 * LCD_HEIGHT);
        lastx = x;
        lasty = y;
        int jx = (int) ((j.x + 1) / 2 * LCD_WIDTH);
        int jy = (int) ((j.y + 1) / 2 * LCD_HEIGHT);
        lastjx = jx;
        lastjy = jy;
        lcd.fillCircle(x, LCD_HEIGHT - y, 5, RGB(0, 0, 0));
        lcd.fillCircle(jx, LCD_HEIGHT - jy, 3, RGB(0, 255, 0));

        _delay_ms(10);
    }
}

