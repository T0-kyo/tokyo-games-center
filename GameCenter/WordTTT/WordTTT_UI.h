/**
 * @file WordTTT_UI.h
 * @brief Defines the UI class for the Word Tic-Tac-Toe variant.
 */
#ifndef WordTTT_UI_H
#define WordTTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "WordTTT_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // toupper()

using namespace std;

/**
 * @class WordTTT_UI
 * @brief Implements the 3x3 Word Tic-Tac-Toe UI
 * Inherits from the template base class UI<char>
 */
class WordTTT_UI : public UI<char> {
public:
    /**
     * @brief The constructor of the class
     */
    WordTTT_UI();

    /**
     * @brief Sets up two players for the game.
     * @return A dynamically allocated array of two Player<char>* pointers.
     */
    virtual Player<char>** setup_players() override;
    
    /**
     * @brief Creates a new Player<char> object.
     * @param name The player's name.
     * @param symbol The player's symbol ('X' or 'O').
     * @param type The type of player.
     * @return A pointer to the newly created Player<char> object.
     */
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    
    /**
     * @brief Gets the player's move input.
     * @param player Pointer to the current Player<char>.
     * @return A pointer to a new Move<char> object.
     */
    virtual Move<char>* get_move(Player<char>* player) override;
    
    /**
     * @brief Helper to show scores.
     * @param board pointer to the board
     */
    void show_score(WordTTT_Board* board);
};

#endif // WordTTT_UI_H