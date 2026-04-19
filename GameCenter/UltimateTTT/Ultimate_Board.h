#ifndef Ultimate_BOARD_H 
#define Ultimate_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Ultimate_Board : public Board<char> {
private:
    char final_board[3][3]; // Each cell represents a small board's status

public:
    Ultimate_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    void update_final_board();
    char get_final_board_cell(int i, int j);
    vector<pair<int, int>> winner;
};

#endif // Ultimate_BOARD_H