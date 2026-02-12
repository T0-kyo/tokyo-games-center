#include "Ultimate_UI.h"
#include "Ultimate_Board.h"
#include <limits> // cin.ignore
#include <cstdlib> // rand()
#include <cctype> // toupper()

/**
 * @brief Constructor for the Ultimate_UI.
 * Initializes the base UI class with a descriptive welcome message and cell width 2.
 */
Ultimate_UI::Ultimate_UI() : UI("\nWelcome to Ultimate Tic-Tac-Toe (9x9)!\nPlay on mini boards to be the ultimate winner!\n", 2) {}

/**
 * @brief Sets up two players for the game.
 * Player 1 uses 'X', Player 2 uses 'O'. Prompts for name and type.
 */
Player<char>** Ultimate_UI::setup_players(){
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Setup Player 1 ---
    string name1 = get_player_name("Player 1 (will use 'X')");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    // --- Setup Player 2 ---
    string name2 = get_player_name("Player 2 (will use 'O')");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);
    return players;
}

/**
 * @brief Creates a new Player<char> object.
 */
Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the player's move input.
 */
Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    char sym = player->get_symbol();
    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn. your symbol is '" << sym << "'." << endl;

    // --- Computer Logic ---
    if (player->get_type() != PlayerType::HUMAN){
        int x,y;
        do{
            x = rand() % 9;
            y = rand() % 9;
        } while ((player->get_board_ptr())->get_board_matrix()[x][y] != ' ');

        cout << "Computer " << player->get_name() << " chose cell (" << x << ", " << y << ") with symbol '" << sym << "'" << endl;
        return new Move<char>(x, y, sym);
    }

    // --- Human Logic ---
    int x, y;

    while(true) {
    cout << "\nEnter the row (0-8) and column (0-8) for your '" << sym << "': ";

    if (!(cin >> x >> y) || x<0 || x>8 || y<0 || y>8){
        cout << "Invalid input. Please enter row(0-8) and column(0-8)." << endl;
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