/**
 * @file FourInARow_UI.h
 * @brief Defines the UI class for the Four in a row variant.
 */
#ifndef FOUR_IN_A_ROW_UI_H
#define FOUR_IN_A_ROW_UI_H

#include "BoardGameFramework/BoardGame_Classes.h"
#include "FourInARow_Board.h"

/**
 * @class FourInARow_UI
 * @brief Implements the 6x7 Four-in-a-row UI
 * Inherits from the template base class UI<char>
 */
class FourInARow_UI : public UI<char> {
public:
    /**
     * @brief The constructor of the class
     */
    FourInARow_UI();

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

#endif // FOUR_IN_A_ROW_UI_H