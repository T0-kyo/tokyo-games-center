#include "MemoryTTT_UI.h"
#include <limits> // For numeric_limits
#include <cstdlib> // For rand()

MemoryTTT_UI::MemoryTTT_UI() : UI("Welcome to Memory Tic-Tac-Toe! (Hidden Identity)\nBoth players will appear as '#'. Remember your moves!", 3) {
}

Player<char>** MemoryTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // We assign internal symbols '1' and '2' so the board logic knows who is who.
    // However, on the screen, the board will only print 'X'.
    
    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, '1', type1);

    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, '2', type2);

    return players;
}

Player<char>* MemoryTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* MemoryTTT_UI::get_move(Player<char>* player) {
    cout << "\n" << player->get_name() << ", it's your turn. (You are hidden as '#')" << endl;

    int x, y;

    // --- Computer Logic ---
    if (player->get_type() == PlayerType::COMPUTER) {
        Board<char>* board = player->get_board_ptr();
        do {
            x = rand() % 3;
            y = rand() % 3;
            // Check visible board to see if space is visually empty
        } while (board->get_board_matrix()[x][y] != ' ');

        cout << "Computer chose: " << x << " " << y << endl;
        return new Move<char>(x, y, player->get_symbol());
    }

    // --- Human Logic ---
    while (true) {
        cout << "Enter row (0-2) and column (0-2): ";
        if (cin >> x >> y) {
            // Check range
            if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
                // Check if visibly empty
                Board<char>* board = player->get_board_ptr();
                if (board->get_board_matrix()[x][y] == ' ') {
                    break; // Valid move
                } else {
                    cout << "That cell is already occupied (by someone)! Try again.\n";
                }
            } else {
                cout << "Invalid coordinates! Use 0-2.\n";
            }
        } else {
            cout << "Invalid input! Please enter numbers.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}