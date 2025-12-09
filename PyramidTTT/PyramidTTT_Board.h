/**
 * @file PyramidTTT_Board.h
 * @brief Defines the board class for the Pyramid Tic-Tac-Toe variant.
 * This game is played on a specialized board that has a pyramid shape.
 */
#ifndef PYRAMIDTTT_BOARD_H
#define PYRAMIDTTT_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <iostream>

using namespace std;

/**
 * @class PyramidTTT_Board
 * @brief Implements the specialized (pyramid) board logic.
 * Inherits from the template base class Board<char>.
 */
class PyramidTTT_Board : public Board<char> {
public:
    /**
     * @brief Constructor for the class
     */
    PyramidTTT_Board();

    // Overridden functions from Board
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
    
    /**
     * @brief Helper to check if  if a specific coordinate is part of the pyramid shape
     */
    bool is_valid_pyramid_cell(int r, int c);
};

#endif // PYRAMIDTTT_BOARD_H