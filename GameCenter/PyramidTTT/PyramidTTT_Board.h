#ifndef PYRAMIDTTT_BOARD_H
#define PYRAMIDTTT_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <iostream>

using namespace std;

class PyramidTTT_Board : public Board<char> {
public:
    PyramidTTT_Board();

    // Overridden functions from Board
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_valid_pyramid_cell(int r, int c);
};

#endif // PYRAMIDTTT_BOARD_H