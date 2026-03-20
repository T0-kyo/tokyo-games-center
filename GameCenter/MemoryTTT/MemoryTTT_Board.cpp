#include "MemoryTTT_Board.h"
#include <iostream>

using namespace std;

MemoryTTT_Board::MemoryTTT_Board() : Board<char>(3, 3) {
    // Initialize both the visible board and the hidden board
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';      // Visible is empty
            real_board[i][j] = ' '; // Hidden is empty
        }
    }
}

bool MemoryTTT_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol(); // This is the unique internal symbol (e.g., '1' or '2')

    // 1. Check bounds
    if (r < 0 || r >= rows || c < 0 || c >= columns) {
        return false;
    }

    // 2. Check occupancy using the REAL board (because visible might have misleading 'X')
    if (real_board[r][c] != ' ') {
        return false;
    }

    // 3. Update the HIDDEN board with the specific player identity
    real_board[r][c] = symbol;

    // 4. Update the VISIBLE board with a generic symbol 'X'
    // This makes both players look exactly the same on screen
    board[r][c] = '#';

    n_moves++;
    return true;
}

bool MemoryTTT_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Check Rows on the HIDDEN board
    for (int i = 0; i < rows; i++) {
        if (real_board[i][0] == sym && real_board[i][1] == sym && real_board[i][2] == sym) {
            return true;
        }
    }

    // Check Columns on the HIDDEN board
    for (int i = 0; i < columns; i++) {
        if (real_board[0][i] == sym && real_board[1][i] == sym && real_board[2][i] == sym) {
            return true;
        }
    }

    // Check Diagonals on the HIDDEN board
    if (real_board[0][0] == sym && real_board[1][1] == sym && real_board[2][2] == sym) {
        return true;
    }
    if (real_board[0][2] == sym && real_board[1][1] == sym && real_board[2][0] == sym) {
        return true;
    }

    return false;
}

char MemoryTTT_Board::get_real_cell(int i, int j){
    return real_board[i][j];
}

bool MemoryTTT_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool MemoryTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool MemoryTTT_Board::is_lose(Player<char>* player) {
    return false;
}