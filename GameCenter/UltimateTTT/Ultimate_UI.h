/**
 * @file Ultimate_UI.h
 * @brief Defines the UI class for the Ultimate Tic-Tac-Toe variant.
 */
#ifndef Ultimate_UI_H
#define Ultimate_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "Ultimate_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // toupper()

using namespace std;

/**
 * @class Ultimate_UI
 * @brief Implements the specialized Ultimate Tic-Tac-Toe UI
 * Inherits from the template base class UI<char>
 */
class Ultimate_UI : public UI<char> {
public:
    /**
     * @brief The constructor of the class
     */
    Ultimate_UI();
    
    /**
     * @brief Sets up two players for the game.
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

#endif // Ultimate_UI_H