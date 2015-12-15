#ifndef ARDUINOGAME_SCORE_H
#define ARDUINOGAME_SCORE_H


class Score {
public:
    Score();
    void add_score(int score);
    void sub_score(int score);
    void set_score(int score);
    int get_score();
    bool has_changed();
private:
    int score;
    bool changed;
};


#endif //ARDUINOGAME_SCORE_H
