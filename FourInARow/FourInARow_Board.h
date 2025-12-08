/**
 * @file FourInARow_Board.h
 * @brief Defines the board class for the Four in a row variant.
 * This game is played on a 6x7 board and involves placing X or O to win
 */
#ifndef FOUR_IN_A_ROW_BOARD_H
#define FOUR_IN_A_ROW_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"

/**
 * @class FourInARow_Board
 * @brief Implements the specialized 6x7 board logic.
 * Inherits from the template base class Board<char>.
 */
class FourInARow_Board : public Board<char> {
public:
    // Constructor: Sets up a 6x7 grid
    FourInARow_Board();

/**
 * @brief Updates the board by adding a move.
 * The move is valid if the cell is in board bounders and the cell is empty.
 * @param move Pointer to the Move<char> object.
 * @return true if the move is successful, false otherwise.
 */
    virtual bool update_board(Move<char>* move) override;

/**
 * @brief Check if player wins
 * Win Condition: Connect 4
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
};

#endif // FOUR_IN_A_ROW_BOARD_H