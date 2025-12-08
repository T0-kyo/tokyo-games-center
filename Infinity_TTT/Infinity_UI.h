/**
 * @file Infinity_UI.h
 * @brief Defines the UI class for the Infinity Tic-Tac-Toe variant.
 */
#ifndef Infinity_UI_H
#define Infinity_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "Infinity_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // لاستخدام دالة toupper()

using namespace std;

/**
 * @class Infinity_UI
 * @brief Implements the 3x3 Infinity Tic-Tac-Toe UI
 * Inherits from the template base class UI<char>
 */
class Infinity_UI : public UI<char> {
public:
    /**
     * @brief The constructor of the class
     */
    Infinity_UI();

    /**
     * @brief Sets up two players for the game.
     * Player 1 uses 'X', Player 2 uses 'O'. Prompts for name and type.
     * @return A dynamically allocated array of two Player<char>* pointers.
     */
    virtual Player<char>** setup_players() override;

    /**
     * @brief Creates a new Player<char> object.
     * @param name The player's name.
     * @param symbol The player's symbol ('X' or 'O').
     * @param type The type of player.
     * @return A pointer to the newly created Player<char> object.
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets the player's move input.
     * @param player Pointer to the current Player<char>.
     * @return A pointer to a new Move<char> object.
     */
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif // Infinity_UI_H