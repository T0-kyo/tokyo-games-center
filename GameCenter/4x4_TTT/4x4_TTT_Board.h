/**
 * @file 4x4_TTT_Board.h
 * @brief Defines the board class for the 4x4 Tic-Tac-Toe variant.
 * This game is played on a 4x4 board and involves moving existing 'X' and 'O' pieces
 * to achieve 3-in-a-row.
 */
#ifndef TTT4x4_Board_H
#define TTT4x4_Board_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class TTT4x4_Board
 * @brief Implements the specialized 4x4 Tic-Tac-Toe board logic.
 * Inherits from the template base class Board<char>. The board is initialized
 * with a set number of 'X' and 'O' pieces, and players attempt to win by moving them.
 */
class TTT4x4_Board : public Board<char> {
    public:
    
    /**
     * @brief Constructor for the TTT4x4_Board.
     */
    TTT4x4_Board();

    /**
     * @brief Updates the board by moving a piece.
     * @param move Pointer to the Move<char> object.
     * @return true if the move was valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;
    
    /**
     * @brief Checks if the current player has won the game.
     * @param player Pointer to the current Player<char> object.
     * @return true if the win condition is met.
     */
    bool is_win(Player<char>* player) override;
    
    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the current Player<char> object.
     * @return true if the game is a draw.
     */
    bool is_draw(Player<char>* player) override;
    
    /**
     * @brief Checks if the game is over (either win or draw).
     * @param player Pointer to the current Player<char> object.
     * @return true if the game has concluded.
     */
    bool game_is_over(Player<char>* player) override;
    
    /**
     * @brief Checks if the current player has lost.
     * @param player Pointer to the current Player<char> object.
     * @return Always returns false (loss is typically implied if the opponent wins).
     */
    bool is_lose(Player<char>* player) override;
};

#endif // TTT4x4_Board_H