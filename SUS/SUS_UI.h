#ifndef SUS_UI_H
#define SUS_UI_H

#include "../BoardGameFramework/BoardGame_Classes.h"
#include "SUS_Board.h" // يجب تضمين ملف البورد الجديد
#include <iostream>
#include <string>
#include <vector>
#include <cctype> // لاستخدام دالة toupper()

using namespace std;

// الكلاس يرث من UI<char>
class SUS_UI : public UI<char> {
public:
    // الكونستركتور
    SUS_UI();

    // --- دوال Overridden ---
    // تهيئة اللاعبين (يتم تعيين رموز مبدئية)
    virtual Player<char>** setup_players() override;
    
    // إنشاء اللاعبين بالنوع الصحيح
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    
    // طلب الحركة (يجب طلب رمز الحركة S أو U)
    virtual Move<char>* get_move(Player<char>* player) override;

    void show_score(SUS_Board* board);
};

#endif // SUS_UI_H