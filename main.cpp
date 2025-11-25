#include <iostream>
#include <string>
#include <vector>
#include <ctime>   // For time()
#include <cstdlib> // For srand() and rand()

// Include the framework
#include "BoardGameFramework/BoardGame_Classes.h"

// Include the headers for your game
#include "NumericalTTT/NumericalTTT_Board.h"
#include "NumericalTTT/NumericalTTT_UI.h"

// You will include your other games here
// #include "SUS/SUS_Board.h"
// #include "SUS/SUS_UI.h"
// ... etc.

using namespace std;

int main() {
    // Seed the random number generator (for computer players)
    // This only needs to be done once
    srand(static_cast<unsigned int>(time(0)));

    // Pointers for Game 9
    Board<int>* numerical_board = nullptr;
    UI<int>* numerical_ui = nullptr;
    Player<int>** numerical_players = nullptr;
    GameManager<int>* numerical_game = nullptr;

    // Pointers for other games will go here...
    // Board<char>* sus_board = nullptr;
    // ...

    int choice;
    while (true) {
        cout << "\n=================================" << endl;
        cout << "  Welcome to the Board Game Center!" << endl;
        cout << "=================================" << endl;
        cout << "Select a game to play:" << endl;
        cout << "1. Numerical Tic-Tac-Toe" << endl;
        // Add your other games here as you make them
        // cout << "2. SUS" << endl;
        // cout << "3. Four-in-a-Row" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // --- Launch Numerical TTT ---
            // 1. Create the UI
            numerical_ui = new NumericalTTT_UI();
            
            // 2. Create the Board
            numerical_board = new NumericalTTT_Board();
            
            // 3. Let the UI create the players
            numerical_players = numerical_ui->setup_players();
            
            // 4. Create the Game Manager
            numerical_game = new GameManager<int>(numerical_board, numerical_players, numerical_ui);
            
            // 5. Run the game
            numerical_game->run();

            // 6. Clean up memory for this game
            delete numerical_game;
            delete numerical_board;
            delete numerical_ui;
            delete numerical_players[0];
            delete numerical_players[1];
            delete[] numerical_players;

        } 
        // else if (choice == 2) { ... launch SUS game ... }
        // ...
        else if (choice == 0) {
            cout << "Thank you for playing!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
