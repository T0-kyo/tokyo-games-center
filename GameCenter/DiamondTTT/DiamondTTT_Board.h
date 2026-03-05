#ifndef DIAMONDTTT_BOARD_H
#define DIAMONDTTT_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <cmath> // For abs()

using namespace std;

class DiamondTTT_Board : public Board<char> {
public:
    DiamondTTT_Board();

    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
    bool is_valid_diamond_cell(int x, int y);

private:
    int count_consecutive(Player<char>* player, int dx, int dy);
};

#endif