/**
 * @file SUS_Board.h
 * @brief Defines the board class for the SUS game.
 * This game is played on a standard 3x3 grid where players place 'S' or 'U'.
 * The goal is to make the most SUS sequences to win.
 */
#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class SUS_Board
 * @brief Implements the 3x3 SUS game logic.
 * Inherits from Board<char> as the board cells (S or U).
 */
class SUS_Board : public Board<char> {
private:
    int p1_score;
    int p2_score;

    /**
     * @brief Helper to count SUS sequences that player made.
     * @param r Row number
     * @param c Column number
     * @return Number of SUS sequences
     */
    int count_sus(int r, int c);

public:
    /**
     * @brief Constructor for the SUS_Board.
     */
    SUS_Board();

    /**
     * @brief Updates the board with a new move (number placement).
     * @param move Pointer to the Move<int> object containing coordinates and the number (symbol).
     * @return true if the move was valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the current player has won the game.
     * @param player Pointer to the current Player<int> object.
     * @return true if the win condition is met.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the current Player<int> object.
     * @return true if the game is a draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game is over (win or draw).
     * @param player Pointer to the current Player<int> object.
     * @return true if the board filled with characters.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Checks if the current player has lost.
     * @param player Pointer to the current Player<int> object.
     * @return true if player's points less than the other's points.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Helper to get the 1st player's points.
     * @return The 1st player's score.
     */
    int get_p1_score() { return p1_score; }
    /**
     * @brief Helper to get the 2nd player's points.
     * @return The 2nd player's score.
     */
    int get_p2_score() { return p2_score; }
};

#endif // SUS_BOARD_H