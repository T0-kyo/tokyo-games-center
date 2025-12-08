#include "5x5_TTT_Board.h"

/**
 * @brief Constructor for the 5x5 Tic-Tac-Toe board.
 * Initializes the 5x5 board with empty spaces and sets initial scores to zero.
 */
TTT5x5_Board::TTT5x5_Board() : Board<char>(5, 5) {
    p1_score = 0;
    p2_score = 0;
    // Initialize the board cells to ' ' (empty)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
}

/**
 * @brief Updates the board with a move.
 */
bool TTT5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    // 1. Check bounds
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    // 2. Check if cell is empty
    if (board[x][y] != ' ')
        return false;

    // 3. Apply the move
    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}

/**
 * @brief Recalculates and updates both P1 ('X') and P2 ('O') scores.
 * This function is the core scoring mechanism, checking all possible 3-in-a-row 
 * patterns across the board for both symbols and updating the internal scores.
 */
void TTT5x5_Board::calculate_final_scores() {
    int x_points = 0;
    int o_points = 0;

    char symbols[] = { 'X', 'O' };
    
    for (char sym : symbols) {
        int current_points = 0;

        // Check rows for 3 in a row (3-wide check in a 5-wide row)
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c <= columns - 3; c++) {
                if (board[r][c] == sym && board[r][c + 1] == sym && board[r][c + 2] == sym) {
                    current_points++;
                }
            }
        }

        // Check columns for 3 in a row (3-high check in a 5-high column)
        for (int c = 0; c < columns; c++) {
            for (int r = 0; r <= rows - 3; r++) {
                if (board[r][c] == sym && board[r + 1][c] == sym && board[r + 2][c] == sym) {
                    current_points++;
                }
            }
        }

        // Check primary diagonals (top-left to bottom-right)
        for (int r = 0; r <= rows - 3; r++) {
            for (int c = 0; c <= columns - 3; c++) {
                if (board[r][c] == sym && board[r + 1][c + 1] == sym && board[r + 2][c + 2] == sym) {
                    current_points++;
                }
            }
        }

        // Check secondary diagonals (top-right to bottom-left)
        for (int r = 0; r <= rows - 3; r++) {
            for (int c = 2; c < columns; c++) { // c starts at 2 (0, 1, 2, 3, 4) to ensure c-2 is valid
                if (board[r][c] == sym && board[r + 1][c - 1] == sym && board[r + 2][c - 2] == sym) {
                    current_points++;
                }
            }
        }

        // Assign the calculated score
        if (sym == 'X') {
            p1_score = current_points;
        } else {
            p2_score = current_points;
        }
    }
}


/**
 * @brief Determines if the current player wins.
 * Win condition: The game is over, and the current player has a strictly higher score.
 */
bool TTT5x5_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }
    
    // When the game is over, calculate final scores for both players
    calculate_final_scores(); 
    
    char sym = player->get_symbol();
    if (sym == 'X') {
        return (p1_score > p2_score);
    } else { // sym == 'O'
        return (p2_score > p1_score);
    }
}

/**
 * @brief Determines if the game is a draw.
 * Draw condition: The game is over, and both players have an equal score.
 */
bool TTT5x5_Board::is_draw(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }

    // When the game is over, calculate final scores for both players
    calculate_final_scores(); 

    return (p1_score == p2_score);
}

/**
 * @brief Determines if the game is over.
 * For this 5x5 scoring game, the game is over when the board is full.
 */
bool TTT5x5_Board::game_is_over(Player<char>* player) {
    return (n_moves == rows * columns);
}

/**
 * @brief Determines if the current player loses.
 * Lose condition: The game is over, and the current player has a strictly lower score.
 */
bool TTT5x5_Board::is_lose(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }
    
    // Scores were calculated in is_win/is_draw call by the GameManager, 
    // but calling it again here is safer if the GameManager doesn't always 
    // call is_win/is_draw before is_lose.
    calculate_final_scores(); 

    char sym = player->get_symbol();
    if (sym == 'X') {
        return (p1_score < p2_score);
    } else { // sym == 'O'
        return (p2_score < p1_score);
    }
}