#ifndef ARDUINOGAME_SCORE_H
#define ARDUINOGAME_SCORE_H

#include <inttypes.h>

class Score {
public:
    Score() : score(0) {

    }
    inline void add_score(uint8_t score) {
        changed = true;
        this->score += score;
    }
    inline void sub_score(uint8_t score) {
        changed = true;
        this->score -= score;
    }
    inline void set_score(uint8_t score) {
        changed = true;
        this->score = score;
    }
    inline int get_score(){
        return score;
    }
    inline bool has_changed() {
        if(changed){
            changed = false;
            return true;
        }

        return false;
    }
private:
    uint16_t score;
    bool changed;
};


#endif //ARDUINOGAME_SCORE_H
