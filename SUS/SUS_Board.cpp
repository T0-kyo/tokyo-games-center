#include "SUS_Board.h"

/**
 * @brief The base constructor for the 3x3 board
 * Initializes the 3x3 board by calling the base constructor.
 */
SUS_Board::SUS_Board() : Board<char>(3, 3) {
    p1_score = 0;
    p2_score = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' '; 
        }
    }
}

/**
 * @brief Helper to count SUS words that player made
 */
int SUS_Board::count_sus(int r, int c) {
    int points = 0;
    
    // Initialize the directions (vertical, horizontal, diagonals)
    // dx, dy are the change in the directions with respect to neighbor cells
    int dr[] = {0, 1, 1, 1}; 
    int dc[] = {1, 0, 1, -1};
    
    if (board[r][0] == 'S' && board[r][1] == 'U' && board[r][2] == 'S') points++; // row
    if (board[0][c] == 'S' && board[1][c] == 'U' && board[2][c] == 'S') points++; // column
    if (r == c) {
        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') points++; // diagonal
    }
    if (r + c == 2) {
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') points++; // off-diagonal
    }

    return points;
}

/**
 * @brief Updates the board with a new move.
 */
bool SUS_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;
    }

    board[r][c] = symbol;
    int gained_points = count_sus(r, c);
    if (n_moves % 2 == 0) {
        p1_score += gained_points;
    } else {
        p2_score += gained_points;
    }

    n_moves++;
    return true;
}

/**
 * @brief Checks if the game is over.
 */
bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves >= 9;
}

/**
 * @brief Checks for a win condition.
 * Win condition is to make the most SUS sequences.
 */
bool SUS_Board::is_win(Player<char>* player) {
    // The game is only won when the board is full
    if (!game_is_over(player)) return false;
    // Identify the player by their symbol
    char symbol = player->get_symbol();

    if (symbol == 'S') { // Player 1
        return p1_score > p2_score; // Wins if P1 score is higher
    } 
    else if (symbol == 'U') { // Player 2
        cout << player -> get_name() << " WINS!\n";
        return p2_score > p1_score; // Wins if P2 score is higher
    }
    
    return false;
}

/**
 * @brief Checks for a draw condition.
 */
bool SUS_Board::is_draw(Player<char>* player) {
    return (game_is_over(player) && p1_score == p2_score);
}

/**
 * @brief Checks if the player has lost.
 */
bool SUS_Board::is_lose(Player<char>* player) {
    // The game is only lost when the board is full
    if (!game_is_over(player)) return false;

    // Check if it's a draw first (equal scores)
    if (p1_score == p2_score) return false;

    char symbol = player->get_symbol();

    if (symbol == 'S') { // Player 1
        return p1_score < p2_score; // Loses if P1 score is lower
    } 
    else if (symbol == 'U') { // Player 2
        return p2_score < p1_score; // Loses if P2 score is lower
    }

    return false;
}