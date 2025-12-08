/**
 * @file ObstaclesTTT_UI.h
 * @brief Defines the UI class for the Obstacles Tic-Tac-Toe variant.
 */
#ifndef OBSTACLES_TTT_UI_H
#define OBSTACLES_TTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "ObstaclesTTT_Board.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * @class ObstaclesTTT_UI
 * @brief Implements the 6x6 Obstacles Tic-Tac-Toe UI
 * Inherits from the template base class UI<char>
 */
class ObstaclesTTT_UI : public UI<char> {
public:
    /**
     * @brief The constructor of the class
     */
    ObstaclesTTT_UI();
    
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

#endif // OBSTACLES_TTT_UI_H