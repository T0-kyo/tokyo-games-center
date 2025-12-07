#ifndef TTT5x5_UI_H
#define TTT5x5_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "5x5_TTT_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> 

using namespace std;

/**
 * @brief Concrete UI class for the 5x5 Scoring Tic-Tac-Toe game.
 * Inherits from UI<char> to handle character moves on a 5x5 board.
 */
class TTT5x5_UI : public UI<char> {
    public:

    TTT5x5_UI();

    // --- Overridden Virtual Functions ---
    virtual Player<char>** setup_players() override;
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the current score of the game.
     * @param board Pointer to the 5x5 board instance.
     */
    void show_score(TTT5x5_Board* board);

};

#endif // TTT5x5_UI_H