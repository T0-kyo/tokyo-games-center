/**
 * @file TTT5x5_UI.h
 * @brief Defines the user interface for the 5x5 Tic-Tac-Toe game.
 */
#ifndef TTT5x5_UI_H
#define TTT5x5_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "5x5_TTT_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // لاستخدام دالة toupper()

using namespace std;

/**
 * @class TTT5x5_UI
 * @brief Handles all user interaction, setup, and move input for 5x5 TTT.
 * Inherits from the base UI<char> class.
 */
class TTT5x5_UI : public UI<char> {
    public:
    /**
     * @brief Constructor for the TTT4x4_UI.
     */
    TTT5x5_UI();

    /**
     * @brief Sets up two players for the 4x4 game.
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
     * @param player Pointer to the current Player<char>.
     * @return A pointer to a new Move<char> object.
     */
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Helper to show the player's score
     * @param board Pointer to the board
     */
    void show_score(TTT5x5_Board* board);

};

#endif // TTT5x5_UI_H