#include "5x5_TTT_UI.h"
#include "5x5_TTT_Board.h"
#include <limits> // For cin.ignore
#include <cstdlib> // For rand()
#include <cctype> // For toupper()

/**
 * @brief Constructor for the 5x5 Tic-Tac-Toe UI.
 * Initializes the base UI class with a descriptive welcome message and cell width 3.
 */
TTT5x5_UI::TTT5x5_UI() : UI("Welcome to Tic-Tac-Toe (5x5)! Get 3 in a row to earn points. The highest score wins after all cells are filled (25 moves).", 3) {}

/**
 * @brief Helper function to display the current scores.
 */
void TTT5x5_UI::show_score(TTT5x5_Board* board) {
    cout << "\n=======================================================" << endl;
    cout << "Current Score: Player X (" << board->get_p1_score() << ") - Player O (" << board->get_p2_score() << ")" << endl;
    cout << "=======================================================" << endl;
}

/**
 * @brief Sets up two players for the game.
 */
Player<char>** TTT5x5_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };
    // Clear any previous bad input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Setup Player 1 ('X') ---
    string name1 = get_player_name("Player 1 (Will use 'X')");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    // --- Setup Player 2 ('O') ---
    string name2 = get_player_name("Player 2 (Will use 'O')");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

/**
 * @brief Creates a Player<char> object of the specified type.
 */
Player<char>* TTT5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    // We use the generic Player<T> class as the base for all types
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the next move from the current player (human or computer).
 */
Move<char>* TTT5x5_UI::get_move(Player<char>* player) {
    char symbol = player->get_symbol();
    string name = player->get_name();

    cout << "\n--- " << name << "'s turn ('" << symbol << "') ---" << endl;

    // Cast the generic Board* to our specific TTT5x5_Board*
    TTT5x5_Board* ttt5x5_Board_ptr = static_cast<TTT5x5_Board*>(player->get_board_ptr());
    
    // Display the current scores before the move
    show_score(ttt5x5_Board_ptr);

    // --- Computer Logic ---
    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        // Simple random move: Keep trying until an empty cell is found
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (ttt5x5_Board_ptr->get_board_matrix()[x][y] != ' ');

        cout << "Computer " << name << " chose cell (" << x << ", " << y << ") with symbol '" << symbol << "'" << endl;
        return new Move<char>(x, y, symbol);
    }

    // --- Human Logic ---
    int x, y;

    while (true) {
        cout << "\nEnter the row (0-4) and column (0-4) for your '" << symbol << "': ";

        if (!(cin >> x >> y) || x < 0 || x > 4 || y < 0 || y > 4) {
            cout << "Invalid input. Please enter valid row (0-4) and column (0-4)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        // Check if the cell is already occupied (this check will be repeated in update_board, but helps with user feedback)
        if (ttt5x5_Board_ptr->get_board_matrix()[x][y] != ' ') {
            cout << "Cell (" << x << ", " << y << ") is already taken. Choose an empty cell." << endl;
            continue;
        }
        // Valid input obtained.
        return new Move<char>(x, y, symbol);
    }
}