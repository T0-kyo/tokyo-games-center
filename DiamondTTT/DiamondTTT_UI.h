#ifndef DIAMONDTTT_UI_H
#define DIAMONDTTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "DiamondTTT_Board.h"
#include <iostream>

using namespace std;

class DiamondTTT_UI : public UI<char> {
public:
    DiamondTTT_UI();

    virtual Player<char>** setup_players() override;
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif