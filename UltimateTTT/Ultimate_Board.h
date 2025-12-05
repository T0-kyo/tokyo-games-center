#ifndef Ultimate_BOARD_H 
#define Ultimate_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Ultimate_Board : public Board<char> {
    private:
    char final_board[3][3]; // Each cell represents a small board's status

    public:
    Ultimate_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    void update_final_board();
};


#endif // Ultimate_BOARD_H