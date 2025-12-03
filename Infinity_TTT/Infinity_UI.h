#ifndef Infinity_UI_H
#define Infinity_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "Infinity_Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // لاستخدام دالة toupper()

using namespace std;

class Infinity_UI : public UI<char> {
    public:

    Infinity_UI();

    virtual Player<char>** setup_players() override;

    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif // Infinity_UI_H