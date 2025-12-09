#include "WordTTT_UI.h"
#include "WordTTT_Board.h"
#include <limits> // cin.ignore
#include <cstdlib> // rand()
#include <cctype> // toupper()

/**
 * @brief The base constructor with a welcome message and a cell width 2.
 */
WordTTT_UI::WordTTT_UI() : UI("\nWelcome to Word Tic-Tac-Toe (3x3)!\nForm more 3-letter valid sequences to win.\n", 2) {}

/**
 * @brief Declare players
 * Handle the type of player (Human or Computer)
 */
Player<char>** WordTTT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1,'X',type1); 

    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

/**
 * @brief Creates a new Player<char> object.
 */
Player<char>* WordTTT_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Gets the player's move input.
 */
Move<char>* WordTTT_UI::get_move(Player<char>* player) {
    char sym1;

    cout << "--------------------------------" << endl;
    cout << player->get_name() << ", it's your turn. Please enter a letter\n" << endl;

    // Show current points
    WordTTT_Board* WordTTT_Board_ptr = static_cast<WordTTT_Board*>(player->get_board_ptr());
    cout << "Current Score: P1 (" << WordTTT_Board_ptr->get_p1_score() << ") - P2 (" << WordTTT_Board_ptr->get_p2_score() << ")" << endl;
    
    // --- Computer player ---
    if (player->get_type() != PlayerType::HUMAN) {
        int x, y;
        
        // Random choice
        do {
            x = rand() % 3;
            y = rand() % 3;
            sym1 = 'A' + (rand() % 26); // Random letter from A-Z
        } while (WordTTT_Board_ptr->get_board_matrix()[x][y] != ' ');

        cout << "Computer " << player->get_name() << " chose cell (" << x << ", " << y << ") and letter '" << sym1 << "'" << endl;
        return new Move<char>(x, y, toupper(sym1));
    }
    
    // --- Human player ---
    int x, y;
    char sym2;
    
    while(true) {
        cout <<"Enter row(0-2), column(0-2), and a letter(A-Z): ";
        if (!(cin >> x >> y >> sym2)) {
        cin.clear();
        cout << "Invalid input format. Please enter number number letter.\n";
        continue;
    }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (x < 0 || x > 2 || y < 0 || y > 2 || !isalpha(sym2)) {
            cout << "Invalid input values. Row and column must be between 0-2, and letter must be A-Z.\n";
            continue;
        }
        break;
    }

    
    return new Move<char>(x, y, toupper(sym2)); 
}

/**
 * @brief Helper to show final score
 */
    void WordTTT_UI::show_score(WordTTT_Board* board) {
        cout << "Final Score: P1 (" << board->get_p1_score() << ") - P2 (" << board->get_p2_score() << ")" << endl;
    }