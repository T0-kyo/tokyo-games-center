#ifndef TTT4x4_UI_H
#define TTT4x4_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "4x4_TTT_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // لاستخدام دالة toupper()

using namespace std;

class TTT4x4_UI : public UI<char> {
    public:

    TTT4x4_UI();

    virtual Player<char>** setup_players() override;

    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    virtual Move<char>* get_move(Player<char>* player) override;

};


#endif // TTT4x4_UI_H