#include "Ultimate_Board.h"

Ultimate_Board::Ultimate_Board() : Board<char>(9,9){
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++){
            board[i][j] = ' ';
        }
    }
    // Initialize final_board to track small board statuses
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            final_board[i][j] = ' ';
        }
    }
}

char Ultimate_Board::get_final_board_cell(int i, int j){
    return final_board[i][j];
}

void Ultimate_Board::update_final_board() {
    char sym1='X', sym2='O';

    //check for X sub-board wins
    for (int i = 0; i < 7; i+=3) {
        for (int j=0; j<7; j+=3){
            for (int k=0; k<3; ++k){
                if (board[i+k][j] == sym1 && board[i+k][j+1] == sym1 && board[i+k][j+2] == sym1) {
                    final_board[i/3][j/3] = sym1;
                }
                if (board[j][i+k] == sym1 && board[j+1][i+k] == sym1 && board[j+2][i+k] == sym1) {
                    final_board[j/3][i/3] = sym1;
                }
            }
            if (board[i][j] == sym1 && board[i+1][j+1] == sym1 && board[i+2][j+2] == sym1){
                final_board[i/3][j/3] = sym1;
            }
            if (board[i][j+2] == sym1 && board[i+1][j+1] == sym1 && board[i+2][j] == sym1){
                final_board[i/3][j/3] = sym1;
            }
        }
    }
    
    //check for O sub-board wins
    for (int i = 0; i < 7; i+=3) {
        for (int j=0; j<7; j+=3){
            for (int k=0; k<3; ++k){
                if (board[i+k][j] == sym2 && board[i+k][j+1] == sym2 && board[i+k][j+2] == sym2) {
                    final_board[i/3][j/3] = sym2;
                }
                if (board[j][i+k] == sym2 && board[j+1][i+k] == sym2 && board[j+2][i+k] == sym2) {
                    final_board[j/3][i/3] = sym2;
                }
            }
            if (board[i][j] == sym2 && board[i+1][j+1] == sym2 && board[i+2][j+2] == sym2){
                final_board[i/3][j/3] = sym2;
            }
            if (board[i][j+2] == sym2 && board[i+1][j+1] == sym2 && board[i+2][j] == sym2){
                final_board[i/3][j/3] = sym2;
            }
        }
    }
}

bool Ultimate_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    
    if (x<0 || x>8 || y<0 || y>8){
        return false;
    }
    if(board[x][y] !=' '){
        return false;
    }

    board[x][y] = move->get_symbol();
    update_final_board();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (final_board[i][j] == 'X'){
                for (int r=i*3; r<i*3 +3; ++r){
                    for (int c=j*3; c<j*3 +3; ++c){
                        board[r][c] = 'X';
                    }
                }
            }
            else if (final_board[i][j] == 'O'){
                for (int r=i*3; r<i*3 +3; ++r){
                    for (int c=j*3; c<j*3 +3; ++c){
                        board[r][c] = 'O';
                    }
                }
            }
        }
    }

    n_moves++;
    return true;
}

bool Ultimate_Board::is_win(Player<char>* player) {
    for (int i = 0; i < 3; ++i) {
        if ((final_board[i][0] == player->get_symbol() && final_board[i][1] == player->get_symbol() && final_board[i][2] == player->get_symbol()) ||
            (final_board[0][i] == player->get_symbol() && final_board[1][i] == player->get_symbol() && final_board[2][i] == player->get_symbol())) {
            return true;
        }
    }
    if ((final_board[0][0] == player->get_symbol() && final_board[1][1] == player->get_symbol() && final_board[2][2] == player->get_symbol()) ||
        (final_board[0][2] == player->get_symbol() && final_board[1][1] == player->get_symbol() && final_board[2][0] == player->get_symbol())) {
        return true;
    }
    return false;
}

bool Ultimate_Board::is_draw(Player<char>* player) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return !is_win(player);
}

bool Ultimate_Board::game_is_over(Player<char>* player) {
    return (is_win(player) || is_draw(player));
}

bool Ultimate_Board::is_lose(Player<char>* player) {
    return false;
}