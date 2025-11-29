#include "ObstaclesTTT_UI.h"
#include <limits>
#include <cstdlib>

ObstaclesTTT_UI::ObstaclesTTT_UI() : UI("\nWelcome to Obstacles Tic-Tac-Toe (6x6)!\nConnect 4 to win. Watch out for random obstacles ('#')!\n", 3) {}

Player<char>** ObstaclesTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name1 = get_player_name("Player 1 (X)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    string name2 = get_player_name("Player 2 (O)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

Player<char>* ObstaclesTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* ObstaclesTTT_UI::get_move(Player<char>* player) {
    // Cast board to access specific methods/grid if needed, though generic board works for display
    cout << "--------------------------------" << endl;
    cout << player->get_name() << " (" << player->get_symbol() << "), it's your turn." << endl;

    // Retrieve the board matrix to check for obstacles
    vector<vector<char>> current_board = player->get_board_ptr()->get_board_matrix();

    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        do {
            x = rand() % 6;
            y = rand() % 6;
        } while (current_board[x][y] != ' '); // Keep trying until empty (not taken and not '#')

        cout << "Computer " << player->get_name() << " chose (" << x << ", " << y << ")" << endl;
        return new Move<char>(x, y, player->get_symbol());
    }

    int x, y;
    while (true) {
        cout << "Enter row (0-5) and column (0-5): ";
        cin >> x >> y;

        if (cin.fail() || x < 0 || x > 5 || y < 0 || y > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid coordinates. Please try again." << endl;
            continue;
        }

        if (current_board[x][y] == '#') {
            cout << "That cell is blocked by an obstacle! Choose another." << endl;
            continue;
        }
        
        if (current_board[x][y] != ' ') {
            cout << "That cell is already taken! Choose another." << endl;
            continue;
        }

        break;
    }

    return new Move<char>(x, y, player->get_symbol());
}