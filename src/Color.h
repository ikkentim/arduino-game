#ifndef ARDUINOGAME_COLOR_H
#define ARDUINOGAME_COLOR_H

#include <inttypes.h>

typedef uint16_t Color;

#ifndef RGB
#define RGB(r,g,b) (Color)(((r&0xF8)<<8)|((g&0xFC)<<3)|((b&0xF8)>>3)) //RGB565: 5 red | 6 green | 5 blue
#endif

#endif //ARDUINOGAME_COLOR_H
