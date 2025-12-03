#include "Infinity_UI.h"
#include "Infinity_Board.h"
#include <limits> // لاستخدام cin.ignore
#include <cstdlib> // لاستخدام rand()
#include <cctype> // لاستخدام toupper()

// Constructor
Infinity_UI::Infinity_UI() : UI("\nWelcome to Infinity Tic-Tac-Toe (3x3)!\nGet 3 in a row to win. But your last move disapears!\n", 2) {}

// Set up players
Player<char>** Infinity_UI::setup_players() {
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

// Create player
Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

// Get move from player
Move<char>* Infinity_UI::get_move(Player<char>* player) {
    char sym = player->get_symbol();
    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn. your symbol is '" << sym << "'." << endl;

    // --- Computer Logic ---
    if (player->get_type() != PlayerType::HUMAN){
        int x,y;
        do{
            x = rand() % 3;
            y = rand() % 3;
        } while ((player->get_board_ptr())->get_board_matrix()[x][y] != ' ');

        cout << "Computer " << player->get_name() << " chose cell (" << x << ", " << y << ") with symbol '" << sym << "'" << endl;
        return new Move<char>(x, y, sym);
    }

    // --- Human Logic ---
    int x, y;

    while(true) {
    cout << "\nEnter the row (0-2) and column (0-2) for your '" << sym << "': ";

    if (!(cin >> x >> y) || x<0 || x>2 || y<0 || y>2){
        cout << "Invalid input. Please enter row(0-2) and column(0-2)." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }

    if ((player->get_board_ptr())->get_board_matrix()[x][y] != ' '){
        cout << "Cell already occupied. Please choose another cell." << endl;
        continue;
    }

    break;
}
    return new Move<char> (x, y, sym);
}