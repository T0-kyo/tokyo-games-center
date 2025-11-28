#include "SUS_Board.h"

SUS_Board::SUS_Board() : Board<char>(3, 3) {
    p1_score = 0;
    p2_score = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' '; 
        }
    }
}

int SUS_Board::count_sus(int r, int c) {
    int points = 0;
    
    // تعريف المتجهات للاتجاهات الأربعة (أفقي، رأسي، قطرين)
    // dx, dy يمثلون التغير في الإحداثيات لفحص الجيران
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

bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves >= 9;
}

// 5. Corrected Winning Logic (Using Symbols)
bool SUS_Board::is_win(Player<char>* player) {
    // The game is only won when the board is full
    if (!game_is_over(player)) return false;
    // Identify the player by their symbol
    char symbol = player->get_symbol();

    if (symbol == 'S') { // Player 1
        return p1_score > p2_score; // Wins if P1 score is higher
    } 
    else if (symbol == 'U') { // Player 2
        return p2_score > p1_score; // Wins if P2 score is higher
    }
    
    return false;
}

bool SUS_Board::is_draw(Player<char>* player) {
    return (game_is_over(player) && p1_score == p2_score);
}

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