#ifndef MEMORYTTT_BOARD_H
#define MEMORYTTT_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY

class MemoryTTT_Board : public Board<char> {
private:
    // Hidden board to track the ACTUAL owner of the cells
    // The public 'board' (inherited) will only show generic 'X' symbols
    char real_board[3][3];

public:
    MemoryTTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    char get_real_cell(int i, int j);
    vector<pair<int, int>> winner;
};

#endif