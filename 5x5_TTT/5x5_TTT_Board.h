#ifndef TTT5x5_BOARD_H
#define TTT5x5_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h" 
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
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
     * This function should be called right before checking the final win/draw condition.
     */
    void calculate_final_scores();

    public:
    TTT5x5_Board();

    // --- Overridden Pure Virtual Functions ---
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;

    // --- Helper functions for the UI ---
    int get_p1_score() const { return p1_score; }
    int get_p2_score() const { return p2_score; }
};

#endif // TTT5x5_BOARD_H