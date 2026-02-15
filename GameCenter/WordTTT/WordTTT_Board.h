/**
 * @file WordTTT_Board.h
 * @brief Defines the board class for the Word Tic-Tac-Toe game.
 * This game is played on a standard 3x3 grid where players place any alphabet character.
 * The goal is to make the most words to win.
 */
#ifndef WordTTT_BOARD_H
#define WordTTT_BOARD_H
#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @class WordTTT_Board
 * @brief Implements the 3x3 Word Tic-Tac-Toe game logic.
 * Inherits from Board<char> as the board cells will contain characters.
 */
class WordTTT_Board : public Board<char> {
private:
    int p1_score; // Player1 points
    int p2_score; // Player2 points
    vector<string> dictionary; // 3-letter words dictionary
    vector<string> used_words; // To track already used words
    /**
     * @brief Helper to check if the word used before in the game or not
     * @param word The word that player made
     * @return true if the word is new
     */
    bool is_new_word(string& word);
    /**
     * @brief Helper to add the points gained to the current player
     * @param player A pointer to the current player
     */
    void add_point(Player<char>* player);


public:
    /**
     * @brief Constructor for the SUS_Board.
     */
    WordTTT_Board();

    /**
     * @brief Helper to load the dictionary of valid words.
     * @param filename Name of the dictionary file
     */
    void load_dictionary(const string& filename);

    /**
     * @brief Helper to check if the word is valid (Exist in the dictionary) or not
     * @param word The word that player made
     * @return true if the word is valid
     */
    bool check_word(string& word);

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

    //Extra funtions for points to display in UI
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

#endif // WordTTT_BOARD_H