#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class SUS_Board : public Board<char> {
private:
    int p1_score;
    int p2_score;
    int count_sus(int r, int c);

public:
    SUS_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    int get_p1_score() { return p1_score; }
    int get_p2_score() { return p2_score; }
};

#endif // SUS_BOARD_H