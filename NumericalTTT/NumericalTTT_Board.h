/**
 * @file NumericalTTT_Board.h
 * @brief Defines the board class for the Numerical Tic-Tac-Toe game.
 * This game is played on a standard 3x3 grid where players place numbers.
 * The goal is to complete a line (row, column, or diagonal) that sums exactly to 15.
 */
#ifndef NUMERICALTTT_BOARD_H
#define NUMERICALTTT_BOARD_H

// Include the framework header from the correct path
#include "BoardGameFramework/BoardGame_Classes.h"
#include <vector>

using namespace std;

/**
 * @class NumericalTTT_Board
 * @brief Implements the 3x3 Numerical Tic-Tac-Toe game logic.
 * Inherits from Board<int> as the board cells store integer values (1-9).
 * Manages the available numbers for each player and checks the 'sum to 15' win condition.
 */
class NumericalTTT_Board : public Board<int> {
private:
    /// Tracks available odd numbers for Player 1 (1, 3, 5, 7, 9)
    vector<int> player1_nums;
    /// Tracks available even numbers for Player 2 (2, 4, 6, 8)
    vector<int> player2_nums;

    /**
     * @brief Helper function to check if three cells complete the winning sum of 15.
     * @param a The number in the first cell.
     * @param b The number in the second cell.
     * @param c The number in the third cell.
     * @return true if a + b + c = 15 and all are non-zero (i.e., filled).
     */
    bool check_sum(int a, int b, int c);

public:
    /**
     * @brief Constructor for the NumericalTTT_Board.
     */
    NumericalTTT_Board();

    // --- Overridden Pure Virtual Functions ---
    
    /**
     * @brief Updates the board with a new move (number placement).
     * @param move Pointer to the Move<int> object containing coordinates and the number (symbol).
     * @return true if the move was valid and applied, false otherwise.
     */
    virtual bool update_board(Move<int>* move) override;
    
    /**
     * @brief Checks if the current player has won the game.
     * @param player Pointer to the current Player<int> object.
     * @return true if the win condition is met.
     */
    virtual bool is_win(Player<int>* player) override;
    
    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the current Player<int> object.
     * @return true if the game is a draw.
     */
    virtual bool is_draw(Player<int>* player) override;
    
    /**
     * @brief Checks if the game is over (win or draw).
     * @param player Pointer to the current Player<int> object.
     * @return true if the game has concluded.
     */
    virtual bool game_is_over(Player<int>* player) override;
    
    /**
     * @brief Checks if the current player has lost.
     * @param player Pointer to the current Player<int> object.
     * @return Always returns false (loss is handled by the opponent winning).
     */
    virtual bool is_lose(Player<int>* player) override;

    // --- Helper functions for the UI ---
    
    /**
     * @brief Gets the list of available odd numbers for Player 1.
     * @return Reference to the vector of available odd numbers.
     */
    vector<int>& get_p1_nums();
    
    /**
     * @brief Gets the list of available even numbers for Player 2.
     * @return Reference to the vector of available even numbers.
     */
    vector<int>& get_p2_nums();
};

#endif // NUMERICALTTT_BOARD_H