/**
 * @file Infinity_Board.h
 * @brief Defines the board class for the Infinity Tic-Tac-Toe variant.
 * This game is played on a 3x3 board and involves placing X or O to win
 */
#ifndef Ininity_BOARD_H 
#define Ininity_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

/**
 * @class Infinity_Board
 * @brief Implements the 3x3 board logic.
 * Inherits from the template base class Board<char>.
 */
class Infinity_Board : public Board<char> {
    private:
        queue<pair<int,int>> del;

    public:
    /**
     * @brief Constructor for the class
     */
    Infinity_Board();

    /**
     * @brief Updates the board by adding a move.
     * @param move Pointer to the Move<char> object.
     * @return true if the move is valid, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player wins
     * @param player Pointer to the current player
     * @return true if the win condition is met
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if it is draw
     * @param player Pointer to the current player
     * @return true if no one wins
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check is game is over
     * @param player Pointer to the current player
     * @return true if the player wins or it is draw
     */
    bool game_is_over(Player<char>* player) override;

    /** @brief Check is player loose
     * @param player Pointer to the current player
     * @return false always
     */
    bool is_lose(Player<char>* player) override;
};


#endif // Ininity_BOARD_H