#include "4x4_TTT_UI.h"
#include "4x4_TTT_Board.h"
#include <limits> // For cin.ignore
#include <cstdlib> // For rand()
#include <cctype> // For toupper()

/**
 * @brief Constructor for the TTT4x4_UI.
 * Initializes the base UI class with a descriptive welcome message and cell width 2.
 */
TTT4x4_UI::TTT4x4_UI() : UI("Welcome to Tic-Tac-Toe (4x4)!\\nMove your pieces to get 3 in a row and win the game!\\n", 2) {}

/**
 * @brief Sets up two players for the 4x4 game.
 * Player 1 uses 'X', Player 2 uses 'O'. Prompts for name and type.
 * @return A dynamically allocated array of two Player<char>* pointers.
 */
Player<char>** TTT4x4_UI::setup_players() {
    Player<char>** players= new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Setup Player 1 (X) ---
    string name1 = get_player_name("Player 1 (Will use 'X')");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    // --- Setup Player 2 (O) ---
    string name2 = get_player_name("Player 2 (Will use 'O')");
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
Player<char>* TTT4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the player's move input, which involves moving an existing piece.
 * This function handles both human and simple computer moves.
 * For a human, it takes the source cell (x, y) and the direction (U, D, R, L).
 * For a computer, it attempts a simple random move.
 * @param player Pointer to the current Player<char>.
 * @return A pointer to a new Move<char> object.
 */
Move<char>* TTT4x4_UI::get_move(Player<char>* player) {
    char sym = player->get_symbol();
    bool is_human = (player->get_type() == PlayerType::HUMAN);

    // Cast the generic Board* to the specific TTT4x4_Board*
    TTT4x4_Board* ttt4x4_Board_ptr = static_cast<TTT4x4_Board*>(player->get_board_ptr());

    // --- Computer Player Logic (Simple Random Move Attempt) ---
    if (!is_human) {
        // This is a very simple random move implementation.
        // It should attempt to find a piece and a valid direction randomly.
        // A full AI would require more complex logic.
        for (int attempt = 0; attempt < 100; ++attempt) {
            int x = rand() % 4;
            int y = rand() % 4;
            char dir_options[] = {'U', 'D', 'R', 'L'};
            char dir = dir_options[rand() % 4];
            // If the cell has the player's symbol, try to create a move
            if (ttt4x4_Board_ptr->get_board_matrix()[x][y] == sym) {
                // Return a move. The Board's update_board will validate it.
                return new Move<char>(x, y, dir);
            }
        }
        // Fallback for computer if no move is found after 100 attempts (unlikely)
        return new Move<char>(-1, -1, 'N');
    }
    // --- Human Player Logic ---
    int x, y;
    char dir;
    
    while (true) {
        cout << player->get_name() << " (" << sym << "), enter coordinates of your piece (row 0-3, col 0-3) and direction (U, D, R, L) to move: ";
        // Get input: row, column, direction
        if (!(cin >> x >> y >> dir)) {
            cout << "Invalid input format. Please enter row, column, and the direction (U, D, R, L)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        dir = toupper(dir);
        // 1. Validate basic input ranges and direction character
        if (x < 0 || x > 3 || y < 0 || y > 3 || (dir != 'U' && dir != 'D' && dir != 'R' && dir != 'L')) {
            cout << "Invalid input range or direction. Please try again." << endl;
            continue;
        }
        // 2. Validate the chosen cell has the player's symbol
        if (ttt4x4_Board_ptr->get_board_matrix()[x][y] != sym) {
            cout << "Cell (" << x << ", " << y << ") does not contain your symbol ('" << sym << "'). Please choose your own piece." << endl;
            continue;
        }
        // 3. Simple validation of the destination cell emptiness (more complex check is in Board::update_board)
        int new_x = x, new_y = y;
        if (dir == 'U') new_x = x - 1;
        else if (dir == 'D') new_x = x + 1;
        else if (dir == 'L') new_y = y - 1;
        else if (dir == 'R') new_y = y + 1;
        
        // Skip validation if the target is out of bounds (Board::update_board handles this)
        if (new_x < 0 || new_x >= 4 || new_y < 0 || new_y >= 4) {
            cout << "Move is out of bounds. Please choose a valid direction." << endl;
            continue;
        }
        if (ttt4x4_Board_ptr->get_board_matrix()[new_x][new_y] != ' ') {
            cout << "Target cell (" << new_x << ", " << new_y << ") is already occupied. Please choose a valid direction." << endl;
            continue;
        }
        
        // Input is valid, create and return the move object
        return new Move<char>(x, y, dir);
    }
}