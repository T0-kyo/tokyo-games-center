#ifndef OBSTACLES_TTT_BOARD_H
#define OBSTACLES_TTT_BOARD_H

#include "../../DEFENITIONS.h"
#include GAME_PLAY
#include <vector>

using namespace std;

class ObstaclesTTT_Board : public Board<char> {
private:
    bool check_line(char a, char b, char c, char d);
    void add_obstacles();
    vector<pair<int, int>> empty;

public:
    ObstaclesTTT_Board();

    // Overridden functions
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
    vector<pair<int, int>> winner;
};

#endif // OBSTACLES_TTT_BOARD_H