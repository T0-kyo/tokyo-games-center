#ifndef TTT5x5_UI_H
#define TTT5x5_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "5x5_TTT_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> 

using namespace std;

/**
 * @brief Concrete UI class for the 5x5 Scoring Tic-Tac-Toe game.
 * Inherits from UI<char> to handle character moves on a 5x5 board.
 */
class TTT5x5_UI : public UI<char> {
    public:
    /**
     * @brief Constructor for the 5x5 Tic-Tac-Toe UI.
     */
    TTT5x5_UI();

    /**
     * @brief Sets up two players for the game.
     * @return A dynamically allocated array of two Player<char> pointers.
     */
    virtual Player<char>** setup_players() override;

    /**
     * @brief Creates a Player<char> object of the specified type.
     * @param name Player's name.
     * @param symbol The symbol ('X' or 'O') used by the player.
     * @param type The type of player (Human, Computer, etc.).
     * @return A dynamically allocated Player<char> pointer.
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets the next move from the current player (human or computer).
     * @param player The current player whose turn it is.
     * @return A dynamically allocated Move<char> pointer.
     */
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the current score of the game.
     * @param board Pointer to the 5x5 board instance.
     */
    void show_score(TTT5x5_Board* board);

};

#endif // TTT5x5_UI_H