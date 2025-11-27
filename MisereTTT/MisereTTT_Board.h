#ifndef TTT_BOARD_H
#define TTT_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"

class TTT_Board : public Board<char> {
public:
    TTT_Board();


    bool update_board(Move<char>* move) override;


    bool is_win(Player<char>* player) override;

    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;

    bool is_lose(Player<char>* player) override;
};

#endif