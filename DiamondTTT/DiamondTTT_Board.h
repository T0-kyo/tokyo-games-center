#ifndef DIAMONDTTT_BOARD_H
#define DIAMONDTTT_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <cmath> // For abs()

using namespace std;

class DiamondTTT_Board : public Board<char> {
public:
    DiamondTTT_Board();

    // --- Overridden Functions ---
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;

    // Helper to check if a specific coordinate is part of the diamond pattern
    bool is_valid_diamond_cell(int x, int y);

private:
    // Helper to count max consecutive marks in a specific direction
    int count_consecutive(Player<char>* player, int dx, int dy);
};

#endif