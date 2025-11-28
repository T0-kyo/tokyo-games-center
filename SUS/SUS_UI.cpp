#include "SUS_UI.h"
#include "SUS_Board.h" // للتأكد من تضمينه
#include <limits> // لاستخدام cin.ignore
#include <cstdlib> // لاستخدام rand()
#include <cctype> // لاستخدام toupper() (لم يعد ضرورياً لكن نتركه للسلامة)

// Constructor
SUS_UI::SUS_UI() : UI("Welcome to Sus! Form S-U-S sequences on the 3x3 grid.", 1) {}

// Override setup_players لتثبيت الرموز ('S' و 'U')
Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // مسح دفاعي للـ input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // --- Setup Player 1: رمز ثابت 'S' ---
    string name1 = get_player_name("Player 1 (Will use 'S')");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'S', type1); 

    // --- Setup Player 2: رمز ثابت 'U' ---
    string name2 = get_player_name("Player 2 (Will use 'U')");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'U', type2);

    return players;
}

// Override create_player
Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

// Override get_move (تم إزالة خيار اختيار الرمز)
Move<char>* SUS_UI::get_move(Player<char>* player) {
    // جلب الرمز الثابت للاعب
    char symbol = player->get_symbol();

    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn. Your symbol is '" << symbol << "'." << endl;

    // --- عرض النقاط الحالية ---
    SUS_Board* Sus_Board_ptr = static_cast<SUS_Board*>(player->get_board_ptr());
    cout << "Current Score: P1 (" << Sus_Board_ptr->get_p1_score() << ") - P2 (" << Sus_Board_ptr->get_p2_score() << ")" << endl;
    
    // --- منطق الكمبيوتر ---
    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        
        // اختيار عشوائي للخلية
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (Sus_Board_ptr->get_board_matrix()[x][y] != ' ');

        cout << "Computer " << player->get_name() << " chose cell (" << x << ", " << y << ") with symbol '" << symbol << "'" << endl;
        return new Move<char>(x, y, symbol);
    }
    
    // --- منطق اللاعب البشري ---
    int x, y;

    cout << "Enter the row (0-2) and column (0-2) for your '" << symbol << "': ";
    // طلب الإحداثيات (x, y) فقط
    while (!(cin >> x >> y) || x < 0 || x > 2 || y < 0 || y > 2) {
        cout << "Invalid input. Please enter valid row (0-2) and column (0-2): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // إرجاع الحركة بالرمز الثابت
    return new Move<char>(x, y, symbol); 
}

void SUS_UI::show_score(SUS_Board* board){
    cout << "Final Score: P1 (" << board->get_p1_score() << ") - P2 (" << board->get_p2_score() << ")" << endl;
}