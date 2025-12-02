#ifndef FOUR_IN_A_ROW_UI_H
#define FOUR_IN_A_ROW_UI_H

#include "BoardGameFramework/BoardGame_Classes.h"
#include "FourInARow_Board.h"

class FourInARow_UI : public UI<char> {
public:
    FourInARow_UI();

    virtual Player<char>** setup_players() override;
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif // FOUR_IN_A_ROW_UI_H