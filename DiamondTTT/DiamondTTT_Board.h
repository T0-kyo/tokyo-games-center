/**
 * @file DiamondTTT_Board.h
 * @brief Defines the board class for the Diamond Tic-Tac-Toe variant.
 * This game is played on a 7x7 board and involves placing X or O to win
 */
#ifndef DIAMONDTTT_BOARD_H
#define DIAMONDTTT_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <cmath> // For abs()

using namespace std;

/**
 * @class DiamondTTT_Board
 * @brief Implements the specialized 7x7 Tic-Tac-Toe board logic.
 * Inherits from the template base class Board<char>.
 */
class DiamondTTT_Board : public Board<char> {
public:
    /**
     * @brief The constructor of the class
     */
    DiamondTTT_Board();

/**
 * @brief Updates the board by adding a move.
 * @param move Pointer to the Move<char> object.
 * @return true if the move is successful, false otherwise.
 */
    virtual bool update_board(Move<char>* move) override;

/**
 * @brief Check if player wins
 * @param player Pointer to the current player
 * @return true if the win condition is met
 */
    virtual bool is_win(Player<char>* player) override;

/**
 * @brief Check if it is draw
 * @param player Pointer to the current player
 * @return true if no one wins
 */
    virtual bool is_draw(Player<char>* player) override;

/**
 * @brief Check is game is over
 * @param player Pointer to the current player
 * @return true if the player wins or it is draw
 */
    virtual bool game_is_over(Player<char>* player) override;

/**
 * @brief Check is player loose
 * @param player Pointer to the current player
 * @return false always
*/
    virtual bool is_lose(Player<char>* player) override;

/**
 * @brief Check if coordinates fall inside the diamond shape
 * @param x Row number
 * @param y Column number
 * @return true if the Manhattan Distance is less than or equal 3
 */
    bool is_valid_diamond_cell(int x, int y);

private:
/**
 * @brief Helper to find the longest line for a player in a specific direction
 * @param player Pointer to the current player
 * @param dx X-direction value
 * @param dy Y-direction value
 * @return the max number
 */
    int count_consecutive(Player<char>* player, int dx, int dy);
};

#endif