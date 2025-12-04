#ifndef MEMORYTTT_UI_H
#define MEMORYTTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <iostream>
#include <string>

using namespace std;

class MemoryTTT_UI : public UI<char> {
public:
    MemoryTTT_UI();

    virtual Player<char>** setup_players() override;
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif