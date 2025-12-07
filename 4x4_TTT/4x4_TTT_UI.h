/**
 * @file 4x4_TTT_UI.h
 * @brief Defines the user interface for the 4x4 Tic-Tac-Toe game.
 */
#ifndef TTT4x4_UI_H
#define TTT4x4_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "4x4_TTT_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // to use toupper()

using namespace std;

/**
 * @class TTT4x4_UI
 * @brief Handles all user interaction, setup, and move input for 4x4 TTT.
 * Inherits from the base UI<char> class and overrides functions to handle
 * the specific requirements of the 4x4 game, such as expecting a direction
 * ('U', 'D', 'R', 'L') instead of just a placement.
 */
class TTT4x4_UI : public UI<char> {
    public:
    /**
     * @brief Constructor for the TTT4x4_UI.
     * Calls the base constructor with the game's welcome message and sets
     * the cell width to 2 characters (default for 'X' and 'O').
     */
    TTT4x4_UI();
    // --- Overridden Virtual Functions ---
    /**
     * @brief Sets up two players for the 4x4 game.
     * Prompts for player names and types (Human/Computer). Player 1 is assigned 'X', Player 2 is assigned 'O'.
     * @return A dynamically allocated array of two Player<char>* pointers.
     */
    virtual Player<char>** setup_players() override;

    /**
     * @brief Factory method to create a Player<char> object.
     * @param name The player's name.
     * @param symbol The player's symbol ('X' or 'O').
     * @param type The type of player (Human, Computer, etc.).
     * @return A pointer to the newly created Player<char> object.
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets the player's move input.
     * Prompts the player for the coordinates of the piece they want to move,
     * and the direction (U, D, R, L) they want to move it.
     * @param player Pointer to the current Player<char>.
     * @return A pointer to a new Move<char> object.
     */
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif // TTT4x4_UI_H