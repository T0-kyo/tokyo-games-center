#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class SUS_Board : public Board<char> {
private:
    int p1_score; // نقاط اللاعب الأول
    int p2_score; // نقاط اللاعب الثاني

    // دالة مساعدة لحساب عدد كلمات SUS التي تكونت بعد حركة معينة
    int count_sus(int r, int c);

public:
    // الكونستركتور
    SUS_Board();

    // الدوال الموروثة من Board
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;

    // دوال إضافية لعرض النقاط في الـ UI
    int get_p1_score() { return p1_score; }
    int get_p2_score() { return p2_score; }
};

#endif // SUS_BOARD_H