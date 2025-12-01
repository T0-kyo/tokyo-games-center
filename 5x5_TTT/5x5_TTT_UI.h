#ifndef TTT5x5_UI_H
#define TTT5x5_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "5x5_TTT_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // لاستخدام دالة toupper()

using namespace std;

class TTT5x5_UI : public UI<char> {
    public:

    TTT5x5_UI();

    virtual Player<char>** setup_players() override;

    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    virtual Move<char>* get_move(Player<char>* player) override;

    void show_score(TTT5x5_Board* board);

};



#endif // TTT5x5_UI_H