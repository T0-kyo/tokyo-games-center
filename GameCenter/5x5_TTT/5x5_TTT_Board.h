/**
 * @file TTT5x5_Board.h
 * @brief Defines the board class for the 5x5 Tic-Tac-Toe variant.
 * This game is played on a 5x5 board and involves placing X or O to make the most
 * three-in-a-row sequences to win.
 */
#ifndef TTT5x5_BOARD_H
#define TTT5x5_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class TTT5x5_Board
 * @brief Implements the specialized 5x5 Tic-Tac-Toe board logic.
 * Inherits from the template base class Board<char>.
 */
class TTT5x5_Board : public Board<char> {
    private:
    int p1_score;
    int p2_score;
    void add_point(Player<char>* player); // scoring function

    public:
    /**
     * @brief Constructor for the TTT5x5_Board.
     */
    TTT5x5_Board();

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

    /**
     * @brief Helper to count 1st player's points
     * @return 1st player's score
     */
    int get_p1_score() { return p1_score; }

    /**
     * @brief Helper to count 2nd player's points
     * @return 2nd player's score
     */
    int get_p2_score() { return p2_score; }
};

#endif // TTT5x5_BOARD_H