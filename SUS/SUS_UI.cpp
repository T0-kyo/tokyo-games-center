#include "SUS_UI.h"
#include "SUS_Board.h"
#include <limits> // cin.ignore
#include <cstdlib> // rand()
#include <cctype> // toupper ()

/**
 * @brief The base constructor with a welcome message and a cell width 2.
 */
SUS_UI::SUS_UI() : UI("\nWelcome to Sus (3x3)!\nForm more S-U-S sequences to win.\n", 2) {}

/**
 * @brief Declare players and initialize their symbol
 * 1st player ('S') and 2nd player ('U')
 * Handle the type of player (Human or Computer)
 */
Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // --- Setup Player 1: 'S' ---
    string name1 = get_player_name("Player 1 (Will use 'S')");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'S', type1); 

    // --- Setup Player 2: 'U' ---
    string name2 = get_player_name("Player 2 (Will use 'U')");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'U', type2);

    return players;
}

/**
 * @brief Creates a new Player<char> object.
 */
Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the player's move input.
 */
Move<char>* SUS_UI::get_move(Player<char>* player) {
    char symbol = player->get_symbol();

    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn. Your symbol is '" << symbol << "'." << endl;

    // --- Show current score ---
    SUS_Board* Sus_Board_ptr = static_cast<SUS_Board*>(player->get_board_ptr());
    cout << "Current Score: P1 (" << Sus_Board_ptr->get_p1_score() << ") - P2 (" << Sus_Board_ptr->get_p2_score() << ")" << endl;
    
    // --- Computer logic ---
    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        
        // Random choice
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (Sus_Board_ptr->get_board_matrix()[x][y] != ' ');

        cout << "Computer " << player->get_name() << " chose cell (" << x << ", " << y << ") with symbol '" << symbol << "'" << endl;
        return new Move<char>(x, y, symbol);
    }
    
    // --- Human logic ---
    int x, y;

    cout << "Enter the row (0-2) and column (0-2) for your '" << symbol << "': ";
    // Git the values (x, y)
    while (!(cin >> x >> y) || x < 0 || x > 2 || y < 0 || y > 2) {
        cout << "Invalid input. Please enter valid row (0-2) and column (0-2): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    return new Move<char>(x, y, symbol); 
}

/**
 * @brief Helper to show the score
 */
void SUS_UI::show_score(SUS_Board* board){
    cout << "Final Score: P1 (" << board->get_p1_score() << ") - P2 (" << board->get_p2_score() << ")" << endl;
}