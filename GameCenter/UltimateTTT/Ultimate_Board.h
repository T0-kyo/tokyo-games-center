/**
 * @file Ultimate_Board.h
 * @brief Defines the board class for the Ultimate Tic-Tac-Toe variant.
 * This game is played on a specialized 9x9 board that has a 3x3 sub boards.
 */
#ifndef Ultimate_BOARD_H 
#define Ultimate_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class Ultimate_Board
 * @brief Implements the specialized (9x9) board logic.
 * Inherits from the template base class Board<char>.
 */
class Ultimate_Board : public Board<char> {
    private:
    char final_board[3][3]; // Each cell represents a small board's status

    public:
    /**
     * @brief Constructor for the class
     */
    Ultimate_Board();
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
    /**
     * @brief Check is player loose
     * @param player Pointer to the current player
     * @return false always
     */
    bool is_lose(Player<char>* player) override;
    /**
     * @brief Helper to update the main board
     */
    void update_final_board();
};

#endif // Ultimate_BOARD_H