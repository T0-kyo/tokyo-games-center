#ifndef PYRAMIDTTT_UI_H
#define PYRAMIDTTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "PyramidTTT_Board.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PyramidTTT_UI : public UI<char> {
public:
    PyramidTTT_UI();
    
    virtual Player<char>** setup_players() override;
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif // PYRAMIDTTT_UI_H