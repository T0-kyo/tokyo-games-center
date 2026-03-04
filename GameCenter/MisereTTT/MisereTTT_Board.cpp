#include "MisereTTT_Board.h"              
#include <iostream>                  

using namespace std;                

/**
 * @brief Constructor for the MisereTTT_Board.
 * Initialize the (3x3) board.
 */
Misere_Board::Misere_Board() : Board<char>(3, 3) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';        
        }
    }
}

/**
 * @brief Updates the board by adding a move.
 */
bool Misere_Board::update_board(Move<char>* move) {
    int r = move->get_x();            
    int c = move->get_y();           
    char symbol = move->get_symbol();
    
    if (r < 0 || r >= rows || c < 0 || c >= columns || board[r][c] != ' ') {
        return false;                
    }

    board[r][c] = symbol;            
    n_moves++;                       
    return true;                  
}

/**
 * @brief Check if player wins
 * Win Condition: DON'T connect 3
 */
bool Misere_Board::is_win(Player<char>* player) {
    return false;                     
}

/**
 * @brief Check if it is draw
 */
bool Misere_Board::is_draw(Player<char>* player) {
    
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief Check is game is over
 */
bool Misere_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Check is player loose.
 * Loose if CONNECT 3
 */
bool Misere_Board::is_lose(Player<char>* player) {
    char sym = player->get_symbol();  

    for (int i = 0; i < rows; i++) {
        
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) {
            return true;          
        }
    }

    for (int i = 0; i < columns; i++) {
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym) {
            return true;             
        }
    }

    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) {
        return true;                
    }
    
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) {
        return true;                 
    }
    return false;                     
}