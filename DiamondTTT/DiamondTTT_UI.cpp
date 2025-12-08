#include "DiamondTTT_UI.h"
#include <cstdlib> // For rand()
#include <limits>  // For clearing buffer
#include <cmath>   // For abs()

/**
 * @brief Constructor for the DiamondTTT_UI.
 * Initializes the base UI class with a descriptive welcome message and cell width 1.
 */
DiamondTTT_UI::DiamondTTT_UI() : UI("Welcome to Diamond Tic-Tac-Toe (7x7)!", 1) {
    // Empty
}

/**
 * @brief Sets up two players for the game.
 * Player 1 uses 'X', Player 2 uses 'O'. Prompts for name and type.
 */
Player<char>** DiamondTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1 (X)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    string name2 = get_player_name("Player 2 (O)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

/**
 * @brief Creates a new Player<char> object.
 */
Player<char>* DiamondTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the player's move input.
 */
Move<char>* DiamondTTT_UI::get_move(Player<char>* player) {
    cout << "--------------------------------" << endl;
    cout << player->get_name() << " (" << player->get_symbol() << "), it's your turn." << endl;

    // --- Computer Player ---
    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        do {
            x = rand() % 7;
            y = rand() % 7;
            // Valid if inside diamond (Distance from center 3,3 <= 3)
        } while ((abs(x - 3) + abs(y - 3)) > 3);

        cout << "Computer chose (" << x << ", " << y << ")" << endl;
        return new Move<char>(x, y, player->get_symbol());
    }

    // --- Human Player ---
    int x, y;

    while (true) {
        cout << "Enter the row (0-6) and column (0-6): ";
        if (cin >> x >> y) {
            // Check grid bounds (0-6)
            if (x >= 0 && x <= 6 && y >= 0 && y <= 6) {
                // Check Diamond Shape Logic
                // Center is at 3,3. Valid distance is <= 3.
                if ((abs(x - 3) + abs(y - 3)) <= 3) {
                    break; 
                } else {
                    cout << "Invalid move! That cell is outside the Diamond shape." << endl;
                }
            } else {
                cout << "Invalid index! Please choose between 0 and 6." << endl;
            }
        } else {
            cout << "Invalid input! Numbers only." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return new Move<char>(x, y, player->get_symbol());
}