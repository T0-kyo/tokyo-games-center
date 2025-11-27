#ifndef NUMERICALTTT_BOARD_H
#define NUMERICALTTT_BOARD_H

// Include the framework header from the correct path
#include "../BoardGameFramework/BoardGame_Classes.h"
#include <vector>

using namespace std;

// This is a concrete class that inherits from a specific version
// of the template base class (Board<int>)
class NumericalTTT_Board : public Board<int> {
private:
    // Tracks available numbers for each player
    vector<int> player1_nums; // Odd: 1, 3, 5, 7, 9
    vector<int> player2_nums; // Even: 2, 4, 6, 8

    // Helper function to check for a win
    bool check_sum(int a, int b, int c);

public:
    // Constructor
    NumericalTTT_Board();

    // --- Overridden Pure Virtual Functions ---
    // These MUST be implemented
    virtual bool update_board(Move<int>* move) override;
    virtual bool is_win(Player<int>* player) override;
    virtual bool is_draw(Player<int>* player) override;
    virtual bool game_is_over(Player<int>* player) override;
    virtual bool is_lose(Player<int>* player) override;

    // --- Helper functions for the UI ---
    // These let the UI show the player what numbers are left
    vector<int>& get_p1_nums();
    vector<int>& get_p2_nums();
};

#endif