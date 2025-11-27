#include "PyramidTTT_UI.h"
#include <limits>
#include <cstdlib>

PyramidTTT_UI::PyramidTTT_UI() : UI("Welcome to Pyramid Tic-Tac-Toe! Align 3 marks to win.", 1) {}

Player<char>** PyramidTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Player 1 is 'X'
    string name1 = get_player_name("Player 1 (X)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    // Player 2 is 'O'
    string name2 = get_player_name("Player 2 (O)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

Player<char>* PyramidTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* PyramidTTT_UI::get_move(Player<char>* player) {
    char symbol = player->get_symbol();
    PyramidTTT_Board* board_ptr = static_cast<PyramidTTT_Board*>(player->get_board_ptr());

    cout << "--------------------------------" << endl;
    cout << player->get_name() << " (" << symbol << "), it's your turn." << endl;
    
    

    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        // Random computer logic: keep guessing until valid cell found
        do {
            x = rand() % 3;
            y = rand() % 5;
        } while (!board_ptr->is_valid_pyramid_cell(x, y) || board_ptr->get_board_matrix()[x][y] != ' ');

        cout << "Computer chose: (" << x << ", " << y << ")" << endl;
        return new Move<char>(x, y, symbol);
    }

    int x, y;
    while (true) {
        cout << "Enter row and column: ";
        if (cin >> x >> y) {
            // Validate logical input before sending to board
            if (board_ptr->is_valid_pyramid_cell(x, y)) {
                break;
            } else {
                cout << "Invalid coordinate! That cell is not part of the pyramid.\n";
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter numbers.\n";
        }
    }

    return new Move<char>(x, y, symbol);
}