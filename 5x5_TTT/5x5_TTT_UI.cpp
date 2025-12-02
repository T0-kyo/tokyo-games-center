#include "5x5_TTT_UI.h"
#include "5x5_TTT_Board.h"
#include <limits> // لاستخدام cin.ignore
#include <cstdlib> // لاستخدام rand()
#include <cctype> // لاستخدام toupper()

// Constructor
TTT5x5_UI::TTT5x5_UI() : UI("\nWelcome to Tic-Tac-Toe (5x5)!\nGet 3 in a row to earn points. Get more points to win!\n", 3) {}

Player<char>** TTT5x5_UI::setup_players() {
    Player<char>** players= new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Setup Player 1 ---
    string name1 = get_player_name("Player 1 (Will use 'X')");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    // --- Setup Player 2 ---
    string name2 = get_player_name("Player 2 (Will use 'O')");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

// Override create_player
Player<char>* TTT5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

// Override get_move
Move<char>* TTT5x5_UI::get_move(Player<char>* player) {
    char symbol = player->get_symbol();

    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn. your symbol is '" << symbol << "'." << endl;


    // --- Show Current Score ---
    TTT5x5_Board* ttt5x5_Board_ptr = static_cast<TTT5x5_Board*>(player->get_board_ptr());
    cout << "Current Score: P1 (" << ttt5x5_Board_ptr->get_p1_score() << ") - P2 (" << ttt5x5_Board_ptr->get_p2_score() << ")" << endl;

    // --- Computer Logic ---
    if (player->get_type() != PlayerType::HUMAN){
        int x, y;
        do{
            x = rand() % 5;
            y = rand() % 5;
        } while (ttt5x5_Board_ptr->get_board_matrix()[x][y] != ' ');

        cout << "Computer " << player->get_name() << " chose cell (" << x << ", " << y << ") with symbol '" << symbol << "'" << endl;
        return new Move<char>(x, y, symbol);
    }

    // --- Human Logic ---
    int x, y;

    while(true) {
    cout << "\nEnter the row (0-4) and column (0-4) for your '" << symbol << "': ";

    if (!(cin >> x >> y) || x<0 || x>4 || y<0 || y>4){
        cout << "Invalid input. Please enter row(0-4) and column(0-4)." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }

    if (ttt5x5_Board_ptr->get_board_matrix()[x][y] != ' '){
        cout << "Cell already occupied. Please choose another cell." << endl;
        continue;
    }

    break;
}
    return new Move<char> (x, y, symbol);
}

void TTT5x5_UI::show_score(TTT5x5_Board* board) {
    cout << "Final Score: Player 1 (" << board->get_p1_score() << ") - Player 2 (" << board->get_p2_score() << ")" << endl;
}
