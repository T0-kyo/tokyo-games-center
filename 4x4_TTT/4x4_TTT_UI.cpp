#include "4x4_TTT_UI.h"
#include "4x4_TTT_Board.h"
#include <limits> // لاستخدام cin.ignore
#include <cstdlib> // لاستخدام rand()
#include <cctype> // لاستخدام toupper()


// Constructor
TTT4x4_UI::TTT4x4_UI() : UI("\nWelcome to Tic-Tac-Toe (4x4)!\nMove your pieces to get 3 in a row and win the game!\n", 2) {}

Player<char>** TTT4x4_UI::setup_players() {
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
Player<char>* TTT4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

// Override get_move
Move<char>* TTT4x4_UI::get_move(Player<char>* player) {
    char sym = player->get_symbol();
    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn. your symbol is '" << sym << "'." << endl;

    // --- Computer Logic ---
TTT4x4_Board* board_ptr = static_cast<TTT4x4_Board*>(player->get_board_ptr());

    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        char sym = player->get_symbol();
        char dirs[4] = { 'U', 'D', 'L', 'R' };

        while (true) {
            // Pick a random cell
            x = rand() % 4;
            y = rand() % 4;

            // Must contain the computer’s symbol
            if (board_ptr->get_board_matrix()[x][y] != sym)
                continue;

            // Try random directions
            char d = dirs[rand() % 4];

            if (d == 'U' && x > 0 && board_ptr->get_board_matrix()[x-1][y] == ' ')
                return new Move<char>(x, y, 'U');

            if (d == 'D' && x < 3 && board_ptr->get_board_matrix()[x+1][y] == ' ')
                return new Move<char>(x, y, 'D');

            if (d == 'L' && y > 0 && board_ptr->get_board_matrix()[x][y-1] == ' ')
                return new Move<char>(x, y, 'L');

            if (d == 'R' && y < 3 && board_ptr->get_board_matrix()[x][y+1] == ' ')
                return new Move<char>(x, y, 'R');

            // Otherwise choose again
        }
}

    // --- Human Logic ---
    int x, y;
    char dir;
    TTT4x4_Board* ttt4x4_Board_ptr = static_cast<TTT4x4_Board*>(player->get_board_ptr());

    while (true){
        cout <<"\nChoose one of your "<< sym <<"'s in row(0-3) and column(0-3) to move (Up, Down, Right, Left):";

        if (!(cin >> x >> y >> dir) || x<0 || x>3 || y<0 || y>3 || (toupper(dir)!='U' && toupper(dir)!='D' && toupper(dir)!='R' && toupper(dir)!='L')) {
        cout << "Invalid input. Please enter row(0-3) and column(0-3) and the direction (U(^), D(v), R(>), L(<))." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }

    if (ttt4x4_Board_ptr->get_board_matrix()[x][y] != sym){
        cout <<"Cell doesn't have your symbol. Please choose a cell that have your symbol" << endl;
        continue;
    }

    if (toupper(dir) == 'U' && (x-1 < 0 || ttt4x4_Board_ptr->get_board_matrix()[x-1][y] != ' ')){
        cout <<"Invalid move. Please choose a valid direction." << endl;
        continue;
    }

    if (toupper(dir) == 'D' && (x+1 > 3 || ttt4x4_Board_ptr->get_board_matrix()[x+1][y] != ' ')){
        cout <<"Invalid move. Please choose a valid direction." << endl;
        continue;
    }

    if (toupper(dir) == 'L' && (y-1 < 0 || ttt4x4_Board_ptr->get_board_matrix()[x][y-1] != ' ')){
        cout <<"Invalid move. Please choose a valid direction." << endl;
        continue;
    }

    if (toupper(dir) == 'R' && (y+1 > 3 || ttt4x4_Board_ptr->get_board_matrix()[x][y+1] != ' ')){
        cout <<"Invalid move. Please choose a valid direction." << endl;
        continue;
    }

    break;
    }

    return new Move<char> (x, y, toupper(dir));
}