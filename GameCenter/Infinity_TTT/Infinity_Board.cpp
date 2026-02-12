#include "Infinity_Board.h"

/**
 * @brief Constructor for the Infinity_Board.
 * Initialize the (3x3) board.
 */
Infinity_Board::Infinity_Board() : Board<char>(3,3){
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++){
            board[i][j] = ' ';
        }
    }
}

/**
 * @brief Updates the board by adding a move.
 */
bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    
    if (x<0 || x>2 || y<0 || y>2){
        return false;
    }
    if(board[x][y] !=' '){
        return false;
    }

    del.push({x,y});
    if (del.size() == 6){
        auto to_del = del.front();
        board[to_del.first][to_del.second] = ' ';
        del.pop();
    }

    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}


/**
 * @brief Check if player wins
 * Win Condition: Connect 3
 */
bool Infinity_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    
    // Check rows and columns for 3 in a row
    for (int i=0; i<3; i++){
        if ((board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) ||
        (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)) {
            return true;
        }
    }
    
    // Check diagonals for 3 in a row
    if ((board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) ||
    (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)) {
        return true;
    }
    
    return false;
}

/**
 * @brief Check if it is draw
 */
bool Infinity_Board::is_draw(Player<char>* player) {
    return false;
}

/**
 * @brief Check is game is over
 */
bool Infinity_Board::game_is_over(Player<char>* player) {
    return (is_win(player) || is_draw(player));
}

/**
 * @brief Check is player loose
 */
bool Infinity_Board::is_lose(Player<char>* player) {
    return false;
}