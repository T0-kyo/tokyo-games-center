#include "FourInARow_Board.h"
#include <iostream>

FourInARow_Board::FourInARow_Board() : Board<char>(6, 7) {
    // Initialize board with spaces
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
}

bool FourInARow_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    // Validate move is within bounds and cell is empty
    // Note: The UI handles finding the correct gravity-based row,
    // so here we just double-check validity.
    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;
    }

    board[r][c] = move->get_symbol();
    n_moves++;
    return true;
}

bool FourInARow_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Check Horizontal (-)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == sym && board[i][j+1] == sym && board[i][j+2] == sym && board[i][j+3] == sym) {
                return true;
            }
        }
    }

    // Check Vertical (|)
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == sym && board[i+1][j] == sym && board[i+2][j] == sym && board[i+3][j] == sym) {
                return true;
            }
        }
    }

    // Check Diagonal (\)
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == sym && board[i+1][j+1] == sym && board[i+2][j+2] == sym && board[i+3][j+3] == sym) {
                return true;
            }
        }
    }

    // Check Anti-Diagonal (/)
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 3; j < columns; j++) {
            if (board[i][j] == sym && board[i+1][j-1] == sym && board[i+2][j-2] == sym && board[i+3][j-3] == sym) {
                return true;
            }
        }
    }

    return false;
}

bool FourInARow_Board::is_draw(Player<char>* player) {
    // Draw if board is full (42 moves) and no winner
    return (n_moves == 42 && !is_win(player));
}

bool FourInARow_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool FourInARow_Board::is_lose(Player<char>* player) {
    return false;
}