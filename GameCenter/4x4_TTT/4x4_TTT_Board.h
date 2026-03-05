#ifndef TTT4x4_Board_H
#define TTT4x4_Board_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class TTT4x4_Board : public Board<char> {
public:
    TTT4x4_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
};

#endif // TTT4x4_Board_H