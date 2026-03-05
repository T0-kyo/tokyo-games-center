#include "WordTTT_Board.h"
#include <fstream>
#include <algorithm>

WordTTT_Board::WordTTT_Board() : Board(3, 3), p1_score(0), p2_score(0){
    // Initialize board with spaces
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';

    // Load dictionary file
    load_dictionary("../dic.txt");
}

void WordTTT_Board::load_dictionary(const string& filename){
    ifstream file(filename);
    string w;

    while (file >> w){
        if (w.size() == 3){
            // upper-case normalize
            transform(w.begin(), w.end(), w.begin(), ::toupper);
            dictionary.push_back(w);
        }
    }
}

bool WordTTT_Board::check_word(string& word){
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    return find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
}

bool WordTTT_Board::is_new_word(string& w){
    if (find(used_words.begin(), used_words.end(), w) != used_words.end())
        return false;

    used_words.push_back(w);
    return true;
}

void WordTTT_Board::add_point(Player<char>* player){
    vector<string> lines;

    // rows
    for (int i = 0; i < 3; i++){
        string w = "";
        for (int j = 0; j < 3; j++)
            w += board[i][j];
        lines.push_back(w);
    }

    // columns
    for (int j = 0; j < 3; j++){
        string w = "";
        for (int i = 0; i < 3; i++)
            w += board[i][j];
        lines.push_back(w);
    }

    // diagonals
    string d1 = { board[0][0], board[1][1], board[2][2] };
    string d2 = { board[0][2], board[1][1], board[2][0] };
    lines.push_back(d1);
    lines.push_back(d2);

    for (string& w : lines){
        if (check_word(w) && is_new_word(w))
        {
            if (player->get_symbol() == 'X')
                p1_score++;
            else
                p2_score++;
        }
    }
}

bool WordTTT_Board::update_board(Move<char>* move){
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    // bounds
    if (x < 0 || x >= 3 || y < 0 || y >= 3)
        return false;

    // cell must be empty
    if (board[x][y] != ' ')
        return false;

    board[x][y] = s;
    n_moves++;

    return true;
}

bool WordTTT_Board::game_is_over(Player<char>* player){
    return (n_moves == 9);
}

bool WordTTT_Board::is_win(Player<char>* player){
    add_point(player); // Update scores
    return (game_is_over(player) && p1_score > p2_score);
}

bool WordTTT_Board::is_draw(Player<char>* player){
    return (game_is_over(player) && p1_score == p2_score);
}

bool WordTTT_Board::is_lose(Player<char>* player){
    return (game_is_over(player) && p1_score < p2_score);
}