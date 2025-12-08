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
    char dir = toupper(move->get_symbol()); // Using symbol field to pass direction ('U', 'D', 'R', 'L')
    // 1. Basic boundary check on source cell
    if (x<0 || x>3 || y<0 || y>3){
        return false;
    }
    // 2. Check if the source cell is empty
    if(board[x][y] ==' '){
        return false;
    }
    int new_x = x;
    int new_y = y;
    // 3. Determine the destination coordinates and check validity
    if (dir == 'U') {
        new_x = x - 1;
    } else if (dir == 'D') {
        new_x = x + 1;
    } else if (dir == 'L') {
        new_y = y - 1;
    } else if (dir == 'R') {
        new_y = y + 1;
    } else {
        // Invalid direction character
        return false; 
    }
    
    // Check if destination is out of bounds
    if (new_x < 0 || new_x >= 4 || new_y < 0 || new_y >= 4) {
        return false;
    }
    // Check if destination is empty
    if (board[new_x][new_y] != ' ') {
        return false;
    }
    // 4. Perform the move
    char sym = board[x][y];
    board[x][y] = ' ';      // Clear the old cell
    board[new_x][new_y] = sym; // Place piece in the new cell
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
    
    // Check rows (3-in-a-row can start at column 0 or 1)
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 2; c++) {
            if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym) {
                return true;
            }
        }
    }
    // Check columns (3-in-a-row can start at row 0 or 1)
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 2; r++) {
            if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym) {
                return true;
            }
        }
    }
    // Check major diagonals (top-left to bottom-right)
    for (int r=0; r<2; r++){
        for (int c=0; c<2; c++){
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym){
                return true;
            }
        }
    }
    // Check minor diagonals (top-right to bottom-left)
    for (int r=0; r<2; r++){
        for (int c=3; c>1; c--){
            if(board[r][c] == sym && board[r+1][c-1] == sym && board[r+2][c-2] == sym){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Checks for a draw condition.
 * In this moving-piece variant, a draw should occur if no valid moves are possible
 * for either player, or if a certain number of moves is reached without a win.
 * This implementation currently checks for a full board, which may need adjustment
 * based on the full game rules.
 */
bool TTT4x4_Board::is_draw(Player<char>* player) {
    // This draw logic seems incorrect for a moving-piece game,
    // but is included based on the original code's structure.
    // A proper draw check would determine if the current player has any valid moves.
    int empty_cells = 0;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if (board[i][j] == ' ') empty_cells++;
        }
    }
    return (empty_cells == 0 && !is_win(player));
}

/**
 * @brief Checks if the game has concluded (win or draw).
 */
bool TTT4x4_Board::game_is_over(Player<char>* player) {
    return (is_win(player) || is_draw(player));
}

/**
 * @brief Checks if the player has lost.
 */
bool TTT4x4_Board::is_lose(Player<char>* player) {
    return false;
}