#ifndef Ininity_BOARD_H 
#define Ininity_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

class Infinity_Board : public Board<char> {
private:
    queue<pair<int,int>> del;

public:
    Infinity_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
};


#endif // Ininity_BOARD_H