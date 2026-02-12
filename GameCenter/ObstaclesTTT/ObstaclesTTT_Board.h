/**
 * @file ObstaclesTTT_Board.h
 * @brief Defines the board class for the Obstacles Tic-Tac-Toe variant.
 * This game is played on a 6x6 board and involves placing X or O to win.
 */
#ifndef OBSTACLES_TTT_BOARD_H
#define OBSTACLES_TTT_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <vector>

using namespace std;

/**
 * @class ObstaclesTTT_Board
 * @brief Implements the 6x6 board logic.
 * Inherits from the template base class Board<char>.
 */
class ObstaclesTTT_Board : public Board<char> {
private:
    /**
     * @brief Helper to check 4 items are the same and not empty or obstacle
     * @param a The 1st character in the line
     * @param b The 2nd character in the line
     * @param c The 3rd character in the line
     * @param d The 4th character in the line
     * @return true if condition is met
     */
    bool check_line(char a, char b, char c, char d);
    
    /**
     * @brief Helper function to add 2 random obstacles to the board
     */
    void add_obstacles();

public:
    /**
     * @brief Constructor for the class
     */
    ObstaclesTTT_Board();

    // Overridden functions
    /**
     * @brief Updates the board by adding a move.
     * @param move Pointer to the Move<char> object.
     * @return true if the move is valid, false otherwise.
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
    /** @brief Check is player loose
     * @param player Pointer to the current player
     * @return false always
     */
    virtual bool is_lose(Player<char>* player) override;
};

#endif // OBSTACLES_TTT_BOARD_H