#include "DiamondTTT_Board.h"
#include <algorithm> // For max()
#include <cmath>     // For abs()

/**
 * @brief Constructor for the DiamondTTT_Board.
 * Initialize the diamond (7x7) board.
 */
DiamondTTT_Board::DiamondTTT_Board() : Board(7, 7) {
    // Initialize cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // If the cell is part of the diamond, make it a playable space ' '
            if (is_valid_diamond_cell(i, j)) {
                board[i][j] = ' ';
            } 
            // If it is OUTSIDE the diamond, fill it with a dot '#' 
            // so the user knows they can't play there.
            else {
                board[i][j] = '#'; 
            }
        }
    }
}

/**
 * @brief Check if coordinates fall inside the diamond shape
 * The center is (3,3). Manhattan Distance must be <= 3.
 */
bool DiamondTTT_Board::is_valid_diamond_cell(int x, int y) {
    return (abs(x - 3) + abs(y - 3)) <= 3;
}

/**
 * @brief Updates the board by adding a move.
 * The move is valid if the cell is in diamond bounders and the cell is empty.
 */
bool DiamondTTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // 1. Check bounds (0-6)
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    // 2. Check if inside Diamond shape
    if (!is_valid_diamond_cell(x, y)) {
        return false;
    }

    // 3. Check if cell is empty (valid cells are initialized to ' ')
    if (board[x][y] != ' ') {
        return false;
    }

    // Valid move
    board[x][y] = symbol;
    n_moves++;
    return true;
}

/**
 * @brief Helper to find the longest line for a player in a specific direction
 */
int DiamondTTT_Board::count_consecutive(Player<char>* player, int dx, int dy) {
    char s = player->get_symbol();
    int max_count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // Optimization: Only start checking if it matches symbol
            if (board[i][j] != s) continue;

            int count = 0;
            int r = i, c = j;
            
            // Trace the line in the given direction
            while (r >= 0 && r < rows && c >= 0 && c < columns && board[r][c] == s) {
                count++;
                r += dx;
                c += dy;
            }
            // Update max found for this specific direction
            if (count > max_count) max_count = count;
        }
    }
    return max_count;
}

/**
 * @brief Check if player wins
 * Win Condition: Line of 3 AND Line of 4 in DIFFERENT directions
 */
bool DiamondTTT_Board::is_win(Player<char>* player) {
    // 1. Get the MAXIMUM consecutive sequence for each distinct direction.
    //* This intentionally collapses multiple lines in the same direction.
    // This prevents "Same Direction" wins automatically.

    int max_horz  = count_consecutive(player, 0, 1);  // Rows
    int max_vert  = count_consecutive(player, 1, 0);  // Columns
    int max_diag1 = count_consecutive(player, 1, 1);  // Main Diag (\)
    int max_diag2 = count_consecutive(player, 1, -1); // Anti Diag (/)
    
    // Store in array for comparison
    // Index: 0=Horz, 1=Vert, 2=Diag1, 3=Diag2
    int lengths[4] = { max_horz, max_vert, max_diag1, max_diag2 };

    // 2. Check pairs of DIFFERENT directions
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            
            if (i == j) continue; //* Skip if directions are the same
            // Condition: One direction has >= 3, OTHER direction has >= 4
            if (lengths[i] >= 3 && lengths[j] >= 4) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Check if it is draw
 */
bool DiamondTTT_Board::is_draw(Player<char>* player) {
    // Total valid cells in a 7x7 diamond is 25.
    return (n_moves == 25 && !is_win(player));
}

/**
 * @brief Check is game is over
 */
bool DiamondTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Check is player loose
 */
bool DiamondTTT_Board::is_lose(Player<char>* player) {
    return false;
}