#ifndef ARDUINOGAME_SCORE_H
#define ARDUINOGAME_SCORE_H

#include <inttypes.h>

class Score {
public:
    Score();
    void add_score(uint8_t score);
    void sub_score(uint8_t score);
    void set_score(uint8_t score);
    int get_score();
    bool has_changed();
private:
    uint16_t score;
    bool changed;
};


#endif //ARDUINOGAME_SCORE_H
