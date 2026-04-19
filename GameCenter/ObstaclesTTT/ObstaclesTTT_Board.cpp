#include "ObstaclesTTT_Board.h"
#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding (done in main, but good to know)

ObstaclesTTT_Board::ObstaclesTTT_Board() : Board<char>(6, 6) {
    // Initialize board with empty spaces
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
}


bool ObstaclesTTT_Board::check_line(char a, char b, char c, char d) {
    return (a != ' ' && a != '#' && a != '*' && a == b && a == c && a == d);
}


void ObstaclesTTT_Board::add_obstacles() {
    empty.clear();
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j){
            if(board[i][j] == ' ') empty.push_back({i, j});
        }
    }

    int c1 = rand() % empty.size();
    board[empty[c1].first][empty[c1].second] = '#';

    empty.clear();
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j){
            if(board[i][j] == ' ') empty.push_back({i, j});
        }
    }
    
    int c2 = rand() % empty.size();
    board[empty[c2].first][empty[c2].second] = '*';
}


bool ObstaclesTTT_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    
    // 1. Check bounds and if cell is empty
    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;
    }

    // 2. Place the player's symbol
    board[r][c] = move->get_symbol();
    n_moves++;

    // 3. Logic: After every round (one turn for each player), add 2 obstacles.
    // If n_moves is even (e.g., 2, 4, 6...), it means Player 2 just played.
    if (n_moves % 2 == 0) {
        add_obstacles();
    }

    return true;
}


bool ObstaclesTTT_Board::is_win(Player<char>* player) {
    // Check Rows (need 4 in a row, so col index goes up to columns - 4)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (check_line(board[i][j], board[i][j+1], board[i][j+2], board[i][j+3])){
                winner.push_back({i, j});
                winner.push_back({i, j+1});
                winner.push_back({i, j+2});
                winner.push_back({i, j+3});
                return true;
            }
        }
    }

    // Check Columns
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j < columns; j++) {
            if (check_line(board[i][j], board[i+1][j], board[i+2][j], board[i+3][j])){
                winner.push_back({i, j});
                winner.push_back({i+1, j});
                winner.push_back({i+2, j});
                winner.push_back({i+3, j});                
                return true;
            }
        }
    }

    // Check Main Diagonals
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (check_line(board[i][j], board[i+1][j+1], board[i+2][j+2], board[i+3][j+3])){
                winner.push_back({i, j});
                winner.push_back({i+1, j+1});
                winner.push_back({i+2, j+2});
                winner.push_back({i+3, j+3});
                return true;
            }
        }
    }

    // Check Anti-Diagonals
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 3; j < columns; j++) {
            if (check_line(board[i][j], board[i+1][j-1], board[i+2][j-2], board[i+3][j-3])){
                winner.push_back({i, j});
                winner.push_back({i+1, j-1});
                winner.push_back({i+2, j-2});
                winner.push_back({i+3, j-3});   
                return true;
            }
        }
    }

    return false;
}


bool ObstaclesTTT_Board::is_draw(Player<char>* player) {
    if (is_win(player)) return false;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (board[i][j] == ' ') return false;
    return true;
}


bool ObstaclesTTT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


bool ObstaclesTTT_Board::is_lose(Player<char>* player) {
    return false;
}