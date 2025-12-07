#include "NumericalTTT_UI.h"
#include <iostream>
#include <cstdlib> // For rand()

/**
 * Constructor: Call the base constructor with a welcome message and a cell width
 * Cell width is 3 spaces (good for numbers)
 */
NumericalTTT_UI::NumericalTTT_UI() : UI("\nWelcome to Numerical Tic-Tac-Toe (3x3)!\nForm 3 numbers sequence that add up to 15 to win.\n", 2) {
    // Constructor body is empty
}

/**
 * @brief Declare players and initialize their valid numbers
 * Handle the type of player (Human or Computer)
 * @return return the list of players
 */
Player<int>** NumericalTTT_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // --- Setup Player 1 (Odd) ---
    string name1 = get_player_name("Player 1 (Odd Numbers)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    // Pass '1' as the symbol (just a placeholder to identify the player)
    players[0] = create_player(name1, 1, type1);

    // --- Setup Player 2 (Even) ---
    string name2 = get_player_name("Player 2 (Even Numbers)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    // Pass '2' as the symbol (placeholder)
    players[1] = create_player(name2, 2, type2);

    return players;
}

/**
 * @brief Override create_player to correctly instantiate Player<int>
 * The base class create_player returns Player<char>, which is a bug.
 * We MUST override it to create the correct type.
 * @return return the REAL players
 */
Player<int>* NumericalTTT_UI::create_player(string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}

/**
 * @brief Helper function to print available numbers
 * @param nums the numbers that player should choose from
 */
void NumericalTTT_UI::display_available_nums(vector<int>& nums) {
    cout << "Available numbers: ";
    for (int n : nums) {
        cout << n << " ";
    }
    cout << endl;
}

/**
 * @brief Override get_move to ask for coordinates and the number
 * Check is the coordinates and the number is valid or not
 * @param player the player that makes the move
 * @return return the new valid move that player made 
 */
Move<int>* NumericalTTT_UI::get_move(Player<int>* player) {
    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn." << endl;

    bool is_player1 = (player->get_symbol() == 1); // Check if Player 1 (Odd)

    // Casting the generic Board* to our NumericalTTT_Board* to access the lists of available numbers.
    NumericalTTT_Board* num_board = static_cast<NumericalTTT_Board*>(player->get_board_ptr());

    // --- Computer Logic ---
    if (player->get_type() != PlayerType::HUMAN) {
        // It picks a random cell and a random available number.
        int x = rand() % 3;
        int y = rand() % 3;

        // Get the correct list of numbers
        vector<int>& nums = is_player1 ? num_board->get_p1_nums() : num_board->get_p2_nums();
        // Pick a random number from the available list
        int rand_index = rand() % nums.size();
        int num = nums[rand_index];

        cout << "Computer " << player->get_name() << " chose cell (" << x << ", " << y << ") and number " << num << endl;
        return new Move<int>(x, y, num);
    }

    // --- Human Player Logic ---
    int x, y, num;

    // Display available numbers for the human
    if (is_player1) {
        display_available_nums(num_board->get_p1_nums());
    }
    else {
        display_available_nums(num_board->get_p2_nums());
    }

    cout << "Enter the row (0-2) and column (0-2) of your move: ";
    cin >> x >> y;

    if (is_player1) {
        cout << "Enter your ODD number: ";
    }
    else {
        cout << "Enter your EVEN number: ";
    }
    cin >> num;

    return new Move<int>(x, y, num);
}