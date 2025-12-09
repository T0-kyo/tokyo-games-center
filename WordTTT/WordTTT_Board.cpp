#include "WordTTT_Board.h"
#include <fstream>
#include <algorithm>

/**
 * @brief The base constructor for the 3x3 board
 * Initializes the 3x3 board by calling the base constructor.
 */
WordTTT_Board::WordTTT_Board() : Board(3, 3), p1_score(0), p2_score(0)
{
    // Initialize board with spaces
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';

    // Load dictionary file
    load_dictionary("../BoardGameFramework/dic.txt");
}

/**
 * @brief Helper to load the dictionary of valid words.
 */
void WordTTT_Board::load_dictionary(const string& filename)
{
    ifstream file(filename);
    string w;

    while (file >> w)
    {
        if (w.size() == 3)
        {
            // upper-case normalize
            transform(w.begin(), w.end(), w.begin(), ::toupper);
            dictionary.push_back(w);
        }
    }
}

/**
 * @brief Helper to check if the word is valid (Exist in the dictionary) or not
 */
bool WordTTT_Board::check_word(string& word)
{
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    return find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
}

/**
 * @brief Helper to check if the word used before in the game or not
 */
bool WordTTT_Board::is_new_word(string& w)
{
    if (find(used_words.begin(), used_words.end(), w) != used_words.end())
        return false;

    used_words.push_back(w);
    return true;
}

/**
 * @brief Helper to add the points gained to the current player
 */
void WordTTT_Board::add_point(Player<char>* player)
{
    vector<string> lines;

    // rows
    for (int i = 0; i < 3; i++)
    {
        string w = "";
        for (int j = 0; j < 3; j++)
            w += board[i][j];
        lines.push_back(w);
    }

    // columns
    for (int j = 0; j < 3; j++)
    {
        string w = "";
        for (int i = 0; i < 3; i++)
            w += board[i][j];
        lines.push_back(w);
    }

    // diagonals
    string d1 = { board[0][0], board[1][1], board[2][2] };
    string d2 = { board[0][2], board[1][1], board[2][0] };
    lines.push_back(d1);
    lines.push_back(d2);

    for (string& w : lines)
    {
        if (check_word(w) && is_new_word(w))
        {
            if (player->get_symbol() == 'X')
                p1_score++;
            else
                p2_score++;
        }
    }
}

/**
 * @brief Updates the board with a new move.
 */
bool WordTTT_Board::update_board(Move<char>* move)
{
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    // bounds
    if (x < 0 || x >= 3 || y < 0 || y >= 3)
        return false;

    // cell must be empty
    if (board[x][y] != ' ')
        return false;

    board[x][y] = s;
    n_moves++;

    return true;
}

/**
 * @brief Checks if the game is over.
 */
bool WordTTT_Board::game_is_over(Player<char>* player)
{
    return (n_moves == 9);
}

/**
 * @brief Checks for a win condition.
 * Win condition is to make as words as you can (more than the other player).
 */
bool WordTTT_Board::is_win(Player<char>* player)
{
    add_point(player); // Update scores
    return (game_is_over(player) && p1_score > p2_score);
}

/**
 * @brief Checks for a draw condition.
 */
bool WordTTT_Board::is_draw(Player<char>* player)
{
    return (game_is_over(player) && p1_score == p2_score);
}

/**
 * @brief Checks if the player has lost.
 */
bool WordTTT_Board::is_lose(Player<char>* player)
{
    return (game_is_over(player) && p1_score < p2_score);
}