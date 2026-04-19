#include "PyramidTTT_Board.h"

PyramidTTT_Board::PyramidTTT_Board() : Board<char>(3, 5) {
    n_moves = 0;
    // Initialize all cells to space
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
    board[0][0]='#'; board[0][1]='#'; board[0][3]='#'; board[0][4]='#';
    board[1][0]='#'; board[1][4]='#';
}

bool PyramidTTT_Board::is_valid_pyramid_cell(int r, int c) {
    // Row 0: Only center (0, 2)
    if (r == 0) return c == 2;
    // Row 1: Middle three (1, 1), (1, 2), (1, 3)
    if (r == 1) return c >= 1 && c <= 3;
    // Row 2: All five (2, 0) to (2, 4)
    if (r == 2) return c >= 0 && c <= 4;
    
    return false;
}

bool PyramidTTT_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    // Check boundaries, if cell is empty, AND if it's a valid part of the pyramid
    if (r < 0 || r >= rows || c < 0 || c >= columns || 
        board[r][c] != ' ' || !is_valid_pyramid_cell(r, c)) {
        return false;
    }

    board[r][c] = symbol;
    n_moves++;
    return true;
}

bool PyramidTTT_Board::is_win(Player<char>* player) {
    // We check for 3 consecutive symbols horizontally, vertically, or diagonally.
    // We don't need to check "who" the player is, just if the board has a winning line
    // matching the last symbol placed, but usually, we check if *this* player won.
    // However, simpler logic checks all lines for consistency.
    
    // Possible Horizontal Wins:
    // Row 1: (1,1)-(1,2)-(1,3)
    if (board[1][1] != ' ' && board[1][1] == board[1][2] && board[1][2] == board[1][3]) {
        winner.push_back({1, 1});
        winner.push_back({1, 2}); 
        winner.push_back({1, 3});
        return true;
    }
    
    // Row 2: (2,0)-(2,1)-(2,2) OR (2,1)-(2,2)-(2,3) OR (2,2)-(2,3)-(2,4)
    if (board[2][0] != ' ' && board[2][0] == board[2][1] && board[2][1] == board[2][2]){
        winner.push_back({2, 0});
        winner.push_back({2, 1}); 
        winner.push_back({2, 2});
        return true;
    }

    if (board[2][1] != ' ' && board[2][1] == board[2][2] && board[2][2] == board[2][3]){
        winner.push_back({2, 1});
        winner.push_back({2, 2}); 
        winner.push_back({2, 3});
        return true;
    }

    if (board[2][2] != ' ' && board[2][2] == board[2][3] && board[2][3] == board[2][4]){
        winner.push_back({2, 2});
        winner.push_back({2, 3}); 
        winner.push_back({2, 4});
        return true;
    }

    // Possible Vertical Wins:
    // Only the center column can form a line of 3: (0,2)-(1,2)-(2,2)
    if (board[0][2] != ' ' && board[0][2] == board[1][2] && board[1][2] == board[2][2]){
        winner.push_back({0, 2});
        winner.push_back({1, 2}); 
        winner.push_back({2, 2});
        return true;
    }

    // Possible Diagonal Wins:
    // Left Diagonal: (0,2)-(1,1)-(2,0)
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        winner.push_back({0, 2});
        winner.push_back({1, 1}); 
        winner.push_back({2, 0});
        return true;
    }
    
    // Right Diagonal: (0,2)-(1,3)-(2,4)
    if (board[0][2] != ' ' && board[0][2] == board[1][3] && board[1][3] == board[2][4]){
        winner.push_back({0, 2});
        winner.push_back({1, 3}); 
        winner.push_back({2, 4});
        return true;
    }

    return false;
}

bool PyramidTTT_Board::is_draw(Player<char>* player) {
    // Total valid cells in pyramid = 1 (top) + 3 (mid) + 5 (bot) = 9 cells.
    return (n_moves == 9 && !is_win(player));
}

bool PyramidTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool PyramidTTT_Board::is_lose(Player<char>* player) {
    return false; // Not needed for standard TTT logic usually
}