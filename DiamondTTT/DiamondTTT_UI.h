/**
 * @file DiamondTTT_UI.h
 * @brief Defines the user interface for the 7x7 diamond Tic-Tac-Toe game.
 */
#ifndef DIAMONDTTT_UI_H
#define DIAMONDTTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "DiamondTTT_Board.h"
#include <iostream>

using namespace std;

/**
 * @class DiamondTTT_UI
 * @brief Implements the 7x7 Tic-Tac-Toe board UI (the diamond shape)
 * Inherits from the template base class UI<char>
 */
class DiamondTTT_UI : public UI<char> {
public:

/**
 * @brief The constructor of the class
 */
    DiamondTTT_UI();

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

#endif