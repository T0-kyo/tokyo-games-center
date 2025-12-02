#ifndef FOUR_IN_A_ROW_BOARD_H
#define FOUR_IN_A_ROW_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"

class FourInARow_Board : public Board<char> {
public:
    // Constructor: Sets up a 6x7 grid
    FourInARow_Board();

    // Core functionality
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
};

#endif // FOUR_IN_A_ROW_BOARD_H