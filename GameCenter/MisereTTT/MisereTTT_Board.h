#ifndef TTT_BOARD_H
#define TTT_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY

class Misere_Board : public Board<char> {
public:
    Misere_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
};

#endif