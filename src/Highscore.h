#ifndef ARDUINOGAME_HIGHSCORE_H
#define ARDUINOGAME_HIGHSCORE_H

#define HIGHSCORE_VALID_CHECK 1337
struct Highscore
{
    int score;
    int check;
    char name[4];

    Highscore() : check(HIGHSCORE_VALID_CHECK){

    }

    bool is_valid() {
        return check == HIGHSCORE_VALID_CHECK;
    }
};
#endif //ARDUINOGAME_HIGHSCORE_H
