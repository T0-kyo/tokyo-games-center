#ifndef NUMERICALTTT_BOARD_H
#define NUMERICALTTT_BOARD_H

// Include the framework header from the correct path
#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>

using namespace std;

class NumericalTTT_Board : public Board<int> {
private:
    /// Tracks available odd numbers for Player 1 (1, 3, 5, 7, 9)
    vector<int> player1_nums;
    /// Tracks available even numbers for Player 2 (2, 4, 6, 8)
    vector<int> player2_nums;

    bool check_sum(int a, int b, int c);

public:
    NumericalTTT_Board();

    // --- Overridden Pure Virtual Functions ---
    virtual bool update_board(Move<int>* move) override;
    virtual bool is_win(Player<int>* player) override;
    virtual bool is_draw(Player<int>* player) override;
    virtual bool game_is_over(Player<int>* player) override;
    virtual bool is_lose(Player<int>* player) override;
    
    // --- Helper functions for the UI ---
    vector<int>& get_p1_nums();
    vector<int>& get_p2_nums();
};

#endif // NUMERICALTTT_BOARD_H