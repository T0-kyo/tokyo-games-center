#ifndef WordTTT_BOARD_H
#define WordTTT_BOARD_H
#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class WordTTT_Board : public Board<char> {
private:
    int p1_score; // Player1 points
    int p2_score; // Player2 points
    vector<string> dictionary; // 3-letter words dictionary
    vector<string> used_words; // To track already used words
    bool is_new_word(string& word);
    void add_point(Player<char>* player);


public:
    WordTTT_Board();

    void load_dictionary(const string& filename);
    bool check_word(string& word);
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;

    //Extra funtions for points to display in UI
    int get_p1_score() { return p1_score; }
    int get_p2_score() { return p2_score; }
};

#endif // WordTTT_BOARD_H