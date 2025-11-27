#ifndef NUMERICALTTT_UI_H
#define NUMERICALTTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "NumericalTTT_Board.h" // Include the board to talk to it
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// This is also a concrete class inheriting from UI<int>
class NumericalTTT_UI : public UI<int> {
private:
    // Helper function to show available numbers
    void display_available_nums(vector<int>& nums);

public:
    // Constructor
    NumericalTTT_UI();

    // --- Overridden Virtual Functions ---
    virtual Player<int>** setup_players() override;
    virtual Player<int>* create_player(string& name, int symbol, PlayerType type) override;
    virtual Move<int>* get_move(Player<int>* player) override;
};

#endif // NUMERICALTTT_UI_H