#ifndef NUMERICALTTT_UI_H
#define NUMERICALTTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "NumericalTTT_Board.h" // Include the board to talk to it
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @class NumericalTTT_UI
 * @brief Handles the NumericalTTT UI
 * Inherits from UI<int>
 */
class NumericalTTT_UI : public UI<int> {
private:
    /**
     * @brief Helper function to display available numbers
     * @param nums Available numbers
     */
    void display_available_nums(vector<int>& nums);

public:
    /** @brief Constructor of the class
     */
    NumericalTTT_UI();

    /**
     * @brief Declare players and initialize their valid numbers
     * Handle the type of player (Human or Computer)
     * @return return the list of players
     */
    virtual Player<int>** setup_players() override;
    /**
     * @brief Override create_player to correctly instantiate Player<int>
     * The base class create_player returns Player<char>, which is a bug.
     * We MUST override it to create the correct type.
     * @return return the REAL players
     */
    virtual Player<int>* create_player(string& name, int symbol, PlayerType type) override;
    /**
     * @brief Override get_move to ask for coordinates and the number
     * Check is the coordinates and the number is valid or not
     * @param player the player that makes the move
     * @return return the new valid move that player made 
     */
    virtual Move<int>* get_move(Player<int>* player) override;
};

#endif // NUMERICALTTT_UI_H