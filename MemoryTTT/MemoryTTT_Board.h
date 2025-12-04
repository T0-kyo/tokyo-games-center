#ifndef MEMORYTTT_BOARD_H
#define MEMORYTTT_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"

class MemoryTTT_Board : public Board<char> {
private:
    // Hidden board to track the ACTUAL owner of the cells
    // The public 'board' (inherited) will only show generic 'X' symbols
    char real_board[3][3];

public:
    MemoryTTT_Board();

    // Validates move, updates hidden board with real owner, 
    // and public board with generic 'X'
    bool update_board(Move<char>* move) override;

    // Checks the hidden board for 3-in-a-row
    bool is_win(Player<char>* player) override;

    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;

    bool is_lose(Player<char>* player) override;
};

#endif