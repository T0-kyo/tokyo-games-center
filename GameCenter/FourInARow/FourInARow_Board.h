#ifndef FOUR_IN_A_ROW_BOARD_H
#define FOUR_IN_A_ROW_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY

class FourInARow_Board : public Board<char> {
public:
    FourInARow_Board();

    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
};

#endif // FOUR_IN_A_ROW_BOARD_H