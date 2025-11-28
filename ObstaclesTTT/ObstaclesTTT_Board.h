#ifndef OBSTACLES_TTT_BOARD_H
#define OBSTACLES_TTT_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <vector>

using namespace std;

class ObstaclesTTT_Board : public Board<char> {
private:
    // Helper function to check for 4 consecutive symbols
    bool check_line(char a, char b, char c, char d);
    
    // Helper function to add 2 random obstacles to the board
    void add_obstacles();

public:
    // Constructor initializes a 6x6 board
    ObstaclesTTT_Board();

    // Overridden functions
    virtual bool update_board(Move<char>* move) override;
    virtual bool is_win(Player<char>* player) override;
    virtual bool is_draw(Player<char>* player) override;
    virtual bool game_is_over(Player<char>* player) override;
    virtual bool is_lose(Player<char>* player) override;
};

#endif // OBSTACLES_TTT_BOARD_H