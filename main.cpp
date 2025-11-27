#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits> // لاستخدام numeric_limits
#include <string>

// تضمين الملفات الأساسية للـ Framework
#include "BoardGameFramework/BoardGame_Classes.h" 

// تضمين ملفات لعبة SUS الجديدة
#include "SUS/SUS_Board.h"
#include "SUS/SUS_UI.h"

#include "PyramidTTT/PyramidTTT_Board.h"
#include "PyramidTTT/PyramidTTT_UI.h"

// تضمين ملفات لعبة Numerical Tic-Tac-Toe (لإكمال المنيو)
#include "NumericalTTT/NumericalTTT_Board.h"
#include "NumericalTTT/NumericalTTT_UI.h"

using namespace std;

// تصريح الدوال (Prototypes)
void run_sus_game();
void run_numerical_ttt_game();
void run_pyramid_ttt_game();

/**
 * @brief الدالة الرئيسية لإنشاء المنيو وتشغيل الألعاب.
 */
int main() {
    // تهيئة مولد الأرقام العشوائية (للاعب الكمبيوتر)
    srand(static_cast<unsigned int>(time(0))); 

    int choice;
    
    do {
        cout << "\n========================================\n";
        cout << "  Welcome to the Board Game Collection!   \n";
        cout << "========================================\n";
        cout << "1. Play SUS Game\n";
        cout << "2. Play Numerical Tic-Tac-Toe\n";
        cout << "3. Play Pyramid Tic-Tac-Toe\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        
        // التعامل مع مدخلات غير صحيحة (Input Validation)
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: 
                run_sus_game(); 
                break;
            case 2: 
                run_numerical_ttt_game(); 
                break;
            case 3:
                run_pyramid_ttt_game();
                break;
            case 0: 
                cout << "Thank you for playing! Goodbye.\n"; 
                break;
            default: 
                cout << "Invalid choice. Please select 1, 2, or 0.\n"; 
                break;
        }
    } while (choice != 0);

    return 0;
}

// -----------------------------------------------------------------

/**
 * @brief دالة تشغيل لعبة SUS.
 */
void run_sus_game() {
    cout << "\n--- Starting SUS Game (Character based) ---\n";
    
    // 1. إنشاء الـ UI والبورد
    UI<char>* ui = new SUS_UI();
    Board<char>* board = new SUS_Board();
    
    // 2. إعداد اللاعبين عبر الـ UI
    Player<char>** players = ui->setup_players();

    // 3. تشغيل مدير اللعبة
    GameManager<char> game(board, players, ui);
    game.run();
    
    // 4. تنظيف الذاكرة
    delete board;
    delete ui;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}

/**
 * @brief دالة تشغيل لعبة Numerical Tic-Tac-Toe.
 */
void run_numerical_ttt_game() {
    cout << "\n--- Starting Numerical Tic-Tac-Toe (Integer based) ---\n";
    
    // 1. إنشاء الـ UI والبورد (باستخدام نوع int)
    UI<int>* ui = new NumericalTTT_UI();
    Board<int>* board = new NumericalTTT_Board();
    
    // 2. إعداد اللاعبين عبر الـ UI
    Player<int>** players = ui->setup_players();

    // 3. تشغيل مدير اللعبة
    GameManager<int> game(board, players, ui);
    game.run();

    // 4. تنظيف الذاكرة
    delete board;
    delete ui;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
    
}
void run_pyramid_ttt_game() {
    cout << "\n--- Starting Pyramid Tic-Tac-Toe ---\n";
    
    // 1. Create UI and Board
    UI<char>* ui = new PyramidTTT_UI();
    Board<char>* board = new PyramidTTT_Board();
    
    // 2. Setup Players
    Player<char>** players = ui->setup_players();

    // 3. Run Game
    GameManager<char> game(board, players, ui);
    game.run();
    
    // 4. Cleanup
    delete board;
    delete ui;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}