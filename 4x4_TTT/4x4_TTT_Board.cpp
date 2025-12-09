#include "4x4_TTT_Board.h"

/**
 * @brief Constructor for the TTT4x4_Board.
 * Initializes the 4x4 board matrix to empty spaces (' ').
 * Then, sets the initial configuration of 'X' and 'O' pieces in the corners:
 * X at (0,1), (0,3), (3,0), (3,2)
 * O at (0,0), (0,2), (3,1), (3,3)
 */
TTT4x4_Board::TTT4x4_Board() : Board<char>(4,4) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++){
            board[i][j] = ' ';
        }
    }
    //Intial X's on the board
    board[0][1]='X';
    board[0][3]='X';
    board[3][0]='X';
    board[3][2]='X';
    //Intial O's on the board
    board[0][0]='O';
    board[0][2]='O';
    board[3][1]='O';
    board[3][3]='O';
}

/**
 * @brief Updates the board by moving a piece.
 * Validates the move direction (U, D, R, L). A move is valid if the source cell
 * contains the player's symbol and the destination cell is empty.
 */
bool TTT4x4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char dir = move->get_symbol(); // Using symbol field to pass direction

    if (x<0 || x>3 || y<0 || y>3){
        return false;
    }
    if(board[x][y] ==' '){
        return false;
    }
    if (dir == 'U' && (x-1 < 0 || board[x-1][y] != ' ')){
        return false;
    }
    if (dir == 'D' && (x+1 > 3 || board[x+1][y] != ' ')){
        return false;
    }
    if (dir == 'L' && (y-1 < 0 || board[x][y-1] != ' ')){
        return false;
    }
    if (dir == 'R' && (y+1 > 3 || board[x][y+1] != ' ')){
        return false;
    }
    if (n_moves % 2 == 0 && board[x][y] !='X'){
        return false;
    }
    if (n_moves % 2 == 1 && board[x][y] !='O'){
        return false;
    }

    if (dir == 'U'){
        if(n_moves % 2 == 0)  board[x-1][y] ='X';
        else board[x-1][y] ='O';
    }
    else if (dir == 'D'){
        if(n_moves % 2 == 0)  board[x+1][y] ='X';
        else board[x+1][y] ='O';    
    }
    else if (dir == 'L'){
        if(n_moves % 2 == 0)  board[x][y-1] ='X';
        else board[x][y-1] ='O';    
    }
    else if (dir == 'R'){
        if(n_moves % 2 == 0)  board[x][y+1] ='X';
        else board[x][y+1] ='O';    
    }

    board[x][y] = ' ';
    n_moves++;
    return true;
}

/**
 * @brief Checks for a win condition (3-in-a-row).
 * Iterates through all possible 3-cell lines (rows, columns, and diagonals)
 * to see if the current player's symbol occupies them.
 */
bool TTT4x4_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    // Check rows
    for (int r=0; r<4; r++){
        if ((board[r][0] == sym && board[r][1] == sym && board[r][2] == sym) || (board[r][1] == sym && board[r][2] == sym && board[r][3] == sym)){
            return true;
        }
    }
    // Check columns
    for (int c=0; c<4; c++){
        if ((board[0][c] == sym && board[1][c] == sym && board[2][c] == sym) || (board[1][c] == sym && board[2][c] == sym && board[3][c] == sym)){
            return true;
        }
    }
    // Check diagonals
    for (int r=0; r<2; r++){
        for (int c=0; c<2; c++){
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym){
                return true;
            }
        }
        for (int c=3; c>1; c--){
            if(board[r][c] == sym && board[r+1][c-1] == sym && board[r+2][c-2] == sym){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Checks if the game has concluded (win or draw).
 */
bool TTT4x4_Board::game_is_over(Player<char>* player) {
    return (is_win(player) || is_draw(player));
}

/**
 * @brief Check is the game is end with draw
 * That happens when the player can't move its pieces
 * All moves is invalid for this player
 */
bool TTT4x4_Board::is_draw(Player<char>* player) {
    int cntX=0, cntO=0;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (board[i][j] == 'X' && (i+1 > 3 || board[i+1][j] != ' ') && 
            (i-1 < 0 || board[i-1][j] != ' ' ) && (j+1 > 3 || board[i][j+1] != ' ' ) && (j-1 < 0 || board[i][j-1] != ' ')){
                cntX++;
            }
        }
    }

    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (board[i][j] == 'O' && (i+1 > 3 || board[i+1][j] != ' ') && 
            (i-1 < 0 || board[i-1][j] != ' ' ) && (j+1 > 3 || board[i][j+1] != ' ' ) && (j-1 < 0 || board[i][j-1] != ' ')){
                cntO++;
            }
        }
    }

    if (cntX==4 || cntO==4){
        return true;
    }

    return false;
}

/**
 * @brief Checks if the player has lost.
 */
bool TTT4x4_Board::is_lose(Player<char>* player) {
    return false;
}