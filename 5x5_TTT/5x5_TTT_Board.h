#ifndef TTT5x5_BOARD_H
#define TTT5x5_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h" 
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class TTT5x5_Board
 * @brief Represents the 5x5 Tic-Tac-Toe board with a scoring system.
 * The game is played on a 5x5 board. Players earn points for every 
 * 3-in-a-row they form. The player with the highest score when the 
 * board is full (25 moves) wins.
 */
class TTT5x5_Board : public Board<char> {
    private:
    int p1_score; // Score for 'X'
    int p2_score; // Score for 'O'
    
    /**
     * @brief Recalculates and updates both p1_score and p2_score based on the current board state.
     */
    void calculate_final_scores();

    public:
    /**
     * @brief Constructor for the 5x5 Tic-Tac-Toe board.
     */
    TTT5x5_Board();

    /**
     * @brief Updates the board with a move.
     * @param move The move object containing (x, y) coordinates and the symbol ('X' or 'O').
     * @return true if the move is valid and applied, false otherwise.
     */
    virtual bool update_board(Move<char>* move) override;
    /**
     * @brief Determines if the current player wins.
     * @param player The player to check for win.
     * @return true if the player wins, false otherwise.
     */
    virtual bool is_win(Player<char>* player) override;

    /**
     * @brief Determines if the game is a draw.
     * @param player Unused parameter from base class signature.
     * @return true if the game is a draw, false otherwise.
     */
    virtual bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over.
     * @param player Unused parameter from base class signature.
     * @return true if the board is full (25 moves), false otherwise.
     */
    virtual bool game_is_over(Player<char>* player) override;

    /**
     * @brief Determines if the current player loses.
     * @param player The player to check for loss.
     * @return true if the player loses, false otherwise.
     */
    virtual bool is_lose(Player<char>* player) override;

    /**
     * @brief Helper to get the player score
     * @return the first player score
     */
    int get_p1_score() const { return p1_score; }

    /**
     * @brief Helper to get the player score
     * @return the second player score
     */
    int get_p2_score() const { return p2_score; }
};

#endif // TTT5x5_BOARD_H