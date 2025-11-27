#ifndef OBSTACLES_TTT_UI_H
#define OBSTACLES_TTT_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "ObstaclesTTT_Board.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ObstaclesTTT_UI : public UI<char> {
public:
    ObstaclesTTT_UI();
    
    virtual Player<char>** setup_players() override;
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif // OBSTACLES_TTT_UI_H