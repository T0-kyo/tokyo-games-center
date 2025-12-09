#include "5x5_TTT_Board.h"

/**
 * @brief Constructor for the TTT5x5_Board.
 * Initializes the 5x5 board matrix to empty spaces (' ').
 */
TTT5x5_Board::TTT5x5_Board() : Board<char>(5,5) {
    p1_score = 0;
    p2_score = 0;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++){
            board[i][j] = ' ';
        }
    }
}

/**
 * @brief Updates the board by moving a piece.
 * A move is valid if the choosen cell is empty and within the bounders.
 */
bool TTT5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    if (x<0 || x>4 || y<0 || y>4)
        return false;

    if(board[x][y] !=' ')
        return false;

    board[x][y] = move->get_symbol();
    n_moves++;
    return true;
}

/**
 * @brief Adds points to the player
 */
void TTT5x5_Board::add_point(Player<char>* player){
    char sym = player->get_symbol();
    int points = 0;

    // Check rows for 3 in a row
    for (int r=0; r<5; r++){
        for (int c=0; c<3; c++){
            if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym){
                    points++;
            }
        }
    }

    // Check columns for 3 in a row
    for (int c=0; c<5; c++){
        for (int r=0; r<3; r++){
            if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym){
                points++;
            }
        }
    }

    // Check diagonals for 3 in a row
    for (int r=0; r<3; r++){
        for (int c=0; c<3; c++){
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym){
                points++;
            }
        }
        for (int c=4; c>1; c--){
            if(board[r][c] == sym && board[r+1][c-1] == sym && board[r+2][c-2] == sym){
                points++;
            }
        }
    }
    

    if(player->get_symbol() == 'X'){
        p1_score = points;
    } else {
        p2_score = points;
    }
}

bool TTT5x5_Board::game_is_over(Player<char>* player) {
    // It must have a free cell at the end of the game.
    return (n_moves == 24);
}
/**
 * @brief Checks the win condition.
 * Win condition is to make the most 3-in-a-row sequences.
 */
bool TTT5x5_Board::is_win(Player<char>* player) {
    add_point(player);
    return (game_is_over(player) && p1_score > p2_score);
}

/**
 * @brief Check if it is a draw.
 * It happens when the game is over and both players have the same points 
 */
bool TTT5x5_Board::is_draw(Player<char>* player) {
    return (game_is_over(player) && p1_score == p2_score); 
}

/**
 * @brief check of the player loose.
 */
bool TTT5x5_Board::is_lose(Player<char>* player) {
    return (game_is_over(player) && p1_score < p2_score);
}