#include "Score.h"

void Score::add_score(uint8_t score) {
    changed = true;

    this->score += score;
}

void Score::sub_score(uint8_t score) {
    changed = true;

    this->score -= score;
}

void Score::set_score(uint8_t score) {
    changed = true;

    this->score = score;
}

int Score::get_score() {
    return score;
}

Score::Score() {
    score = 0;
}

bool Score::has_changed() {
    if(changed){
        changed = false;
        return true;
    }

    return false;
}
