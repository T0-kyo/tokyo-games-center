#include "FourInARow_UI.h"
#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

/**
 * @brief Constructor for the FourInARow_UI.
 * Initializes the base UI class with a descriptive welcome message and cell width 3.
 */
FourInARow_UI::FourInARow_UI() : UI("Welcome to Four-in-a-Row!\nConnect 4 marks horizontally, vertically, or diagonally.", 3) {}

/**
 * @brief Sets up two players for the game.
 * Player 1 uses 'X', Player 2 uses 'O'. Prompts for name and type.
 * @return A dynamically allocated array of two Player<char>* pointers.
 */
Player<char>** FourInARow_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // Clear buffer before getting names
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

/**
 * @brief Creates a new Player<char> object.
 * @param name The player's name.
 * @param symbol The player's symbol ('X' or 'O').
 * @param type The type of player.
 * @return A pointer to the newly created Player<char> object.
 */
Player<char>* FourInARow_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the player's move input.
 * @param player Pointer to the current Player<char>.
 * @return A pointer to a new Move<char> object.
 */
Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    cout << "--------------------------------" << endl;
    cout << player->get_name() << " (" << player->get_symbol() << "), enter a column number (0-6)." << endl;

    // We need to access the board matrix to calculate gravity (where the token falls)
    vector<vector<char>> boardMatrix = player->get_board_ptr()->get_board_matrix();
    int rows = 6;
    int cols = 7;

    int selected_col = -1;
    int calculated_row = -1;

    // --- Computer Logic ---
    if (player->get_type() != PlayerType::HUMAN) {
        // Simple Random AI that tries to find a valid column
        do {
            selected_col = rand() % cols;
            // Check if column is not full (top cell must be empty)
            if (boardMatrix[0][selected_col] == ' ') {
                 // Find the lowest empty row in this column
                for (int i = rows - 1; i >= 0; i--) {
                    if (boardMatrix[i][selected_col] == ' ') {
                        calculated_row = i;
                        break;
                    }
                }
            } else {
                selected_col = -1; // Try again if column is full
            }
        } while (selected_col == -1);

        cout << "Computer chose column " << selected_col << endl;
        return new Move<char>(calculated_row, selected_col, player->get_symbol());
    }

    // --- Human Logic ---
    while (true) {
        cout << "Column (0-6): ";
        cin >> selected_col;

        // 1. Validate Input
        if (cin.fail() || selected_col < 0 || selected_col >= cols) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid column. Please enter 0-6." << endl;
            continue;
        }

        // 2. Check if column is full (top row must be empty)
        if (boardMatrix[0][selected_col] != ' ') {
            cout << "Column " << selected_col << " is full! Choose another." << endl;
            continue;
        }

        // 3. Apply Gravity: Find the bottom-most empty row
        for (int i = rows - 1; i >= 0; i--) {
            if (boardMatrix[i][selected_col] == ' ') {
                calculated_row = i;
                break;
            }
        }
        
        break; // Valid move found
    }

    return new Move<char>(calculated_row, selected_col, player->get_symbol());
}