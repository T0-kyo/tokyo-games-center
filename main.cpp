#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

// Framework
#include "BoardGameFramework/BoardGame_Classes.h"

// SUS Game
#include "SUS/SUS_Board.h"
#include "SUS/SUS_UI.h"

// Pyramid Tic-Tac-Toe
#include "PyramidTTT/PyramidTTT_Board.h"
#include "PyramidTTT/PyramidTTT_UI.h"

// Numerical Tic-Tac-Toe
#include "NumericalTTT/NumericalTTT_Board.h"
#include "NumericalTTT/NumericalTTT_UI.h"
#include "MisereTTT/MisereTTT_Board.h"
#include "MisereTTT/MisereTTT_UI.h"

// Word Tic-Tac-Toe
#include "WordTTT/WordTTT_Board.h"
#include "WordTTT/WordTTT_UI.h"

using namespace std;

// Function declarations
void run_sus_game();
void run_numerical_ttt_game();
void run_pyramid_ttt_game();
void run_word_ttt_game();
void run_MisereTTT_game();

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    do {
        cout << "\n========================================\n";
        cout << "        Board Game Collection\n";
        cout << "========================================\n";
        cout << "1. Play SUS Game\n";
        cout << "2. Play Numerical Tic-Tac-Toe\n";
        cout << "3. Play Pyramid Tic-Tac-Toe\n";
        cout << "4. Play Word Tic-Tac-Toe\n";
        cout << "5. Play Misere Tic-Tac-Toe\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            run_sus_game();
            break;
        case 2:
            run_numerical_ttt_game();
            break;
        case 3:
            run_pyramid_ttt_game();
            break;
        case 4:
            run_word_ttt_game();
            break;
        case 5:
            run_MisereTTT_game();
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}

// ---------------------------------------------------------------

void run_sus_game() {
    cout << "\n--- Starting SUS Game ---\n";

    UI<char>* ui = new SUS_UI();
    Board<char>* board = new SUS_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_numerical_ttt_game() {
    cout << "\n--- Starting Numerical Tic-Tac-Toe ---\n";

    UI<int>* ui = new NumericalTTT_UI();
    Board<int>* board = new NumericalTTT_Board();

    Player<int>** players = ui->setup_players();

    GameManager<int> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_pyramid_ttt_game() {
    cout << "\n--- Starting Pyramid Tic-Tac-Toe ---\n";

    UI<char>* ui = new PyramidTTT_UI();
    Board<char>* board = new PyramidTTT_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_word_ttt_game() {
    cout << "\n--- Starting Word Tic-Tac-Toe ---\n";

    UI<char>* ui = new WordTTT_UI();
    Board<char>* board = new WordTTT_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_MisereTTT_game() {
    cout << "\n--- Starting Standard Tic-Tac-Toe ---\n"; 
    
    UI<char>* ui = new TTT_UI();            
    Board<char>* board = new TTT_Board();   
    
   
    Player<char>** players = ui->setup_players(); 

    GameManager<char> game(board, players, ui);
    
    game.run();                           
    
    delete board;                           
    delete ui;                              
    for (int i = 0; i < 2; ++i) {
        delete players[i];                 
    }
    delete[] players;                      
}