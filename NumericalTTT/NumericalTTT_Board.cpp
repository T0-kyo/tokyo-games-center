#include "NumericalTTT_Board.h"
#include <algorithm> // For std::find
#include <numeric>   // For std::accumulate

/**
 * Constructor: Call the base constructor for a 3x3 board
 * Initializes the 3x3 board by calling the base constructor and setting
 * the initial available number lists (P1: {1, 3, 5, 7, 9}, P2: {2, 4, 6, 8}).
 */
NumericalTTT_Board::NumericalTTT_Board() : Board(3, 3) {
    // Initialize available number lists
    player1_nums = { 1, 3, 5, 7, 9 };
    player2_nums = { 2, 4, 6, 8 };

    // Initialize the board cells to 0 (which means empty)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = 0;
        }
    }
}

/**
 * @brief Checks if three numbers form the winning sum of 15.
 * @param a The number in the first cell.
 * @param b The number in the second cell.
 * @param c The number in the third cell.
 * @return true if the cells are filled and sum to 15.
 */
bool NumericalTTT_Board::check_sum(int a, int b, int c) {
    // A line only wins if all 3 cells are filled (non-zero)
    if (a != 0 && b != 0 && c != 0) {
        return (a + b + c) == 15;
    }
    return false;
}

/**
 * @brief Updates the board with a new move.
 * Implements complex validation logic: checks coordinates, cell emptiness,
 * player parity (Odd/Even), and availability of the chosen number.
 * If valid, the number is placed, and removed from the player's available list.
 * @param move Pointer to the move object containing the coordinates (x, y) and the number (num).
 * @return true if the move is valid and applied, false otherwise.
 */
bool NumericalTTT_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol(); // The "symbol" is the number being played
    // 1. Check if (x, y) is within the board bounds
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false; // Invalid move
    }
    // 2. Check if the cell is already taken (it must be 0)
    if (board[x][y] != 0) {
        return false; // Invalid move
    }
    // 3. Determine which player is moving (Player 1 is 0, Player 2 is 1)
    bool is_player1_turn = (n_moves % 2 == 0);
    vector<int>* current_player_nums;
    if (is_player1_turn) {
        current_player_nums = &player1_nums;
    }
    else {
        current_player_nums = &player2_nums;
    }
    // 4. Check if the number is valid and available for this player
    auto it = find(current_player_nums->begin(), current_player_nums->end(), num);
    if (it == current_player_nums->end()) {
        // The number is not in the player's available list
        return false; // Invalid move
    }
    // --- If all checks pass, the move is valid ---
    // 5. Place the number on the board
    board[x][y] = num;
    // 6. Remove the number from the player's list
    current_player_nums->erase(it);
    // 7. Increment the total move count
    n_moves++;
    // 8. Return true to signal a successful move
    return true;
}

/**
 * @brief Checks for a win condition (any line sums to 15).
 * @param player Pointer to the current Player<int>.
 * @return true if a win is detected (row, column, or diagonal).
 */
bool NumericalTTT_Board::is_win(Player<int>* player) {
    // Check rows
    for (int i = 0; i < rows; ++i) {
        if (check_sum(board[i][0], board[i][1], board[i][2])) return true;
    }
    // Check columns
    for (int j = 0; j < columns; ++j) {
        if (check_sum(board[0][j], board[1][j], board[2][j])) return true;
    }
    // Check diagonals
    if (check_sum(board[0][0], board[1][1], board[2][2])) return true;
    if (check_sum(board[0][2], board[1][1], board[2][0])) return true;
    // No win condition found
    return false;
}

/**
 * @brief Checks for a draw condition.
 * @param player Pointer to the current Player<int>.
 * @return true if the board is full (9 moves) and there is no winner.
 */
bool NumericalTTT_Board::is_draw(Player<int>* player) {
    // A draw happens if the board is full (9 moves) and there is no winner
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief Checks if the game is over.
 * @param player Pointer to the current Player<int>.
 * @return true if there is a win or a draw.
 */
bool NumericalTTT_Board::game_is_over(Player<int>* player) {
    // The game is over if there is a win or a draw
    return (is_win(player) || is_draw(player));
}

/**
 * @brief Checks if the player has lost.
 * @param player Pointer to the current Player<int>.
 * @return Always returns false in this implementation.
 */
bool NumericalTTT_Board::is_lose(Player<int>* player) {
    // This game doesn't have a specific "lose" condition
    return false;
}

// --- Helper function implementations ---
/**
 * @brief Provides access to the list of available odd numbers.
 * @return Reference to the vector of available odd numbers.
 */
vector<int>& NumericalTTT_Board::get_p1_nums() {
    return player1_nums;
}

/**
 * @brief Provides access to the list of available even numbers.
 * @return Reference to the vector of available even numbers.
 */
vector<int>& NumericalTTT_Board::get_p2_nums() {
    return player2_nums;
}