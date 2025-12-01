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

// Misere Tic-Tac-Toe
#include "MisereTTT/MisereTTT_Board.h" 
#include "MisereTTT/MisereTTT_UI.h"

// Obstacles Tic-Tac-Toe
#include "ObstaclesTTT/ObstaclesTTT_Board.h" 
#include "ObstaclesTTT/ObstaclesTTT_UI.h"

// Word Tic-Tac-Toe
#include "WordTTT/WordTTT_Board.h"
#include "WordTTT/WordTTT_UI.h"

// 5x5 Tic-Tac-Toe
#include "5x5_TTT/5x5_TTT_Board.h"
#include "5x5_TTT/5x5_TTT_UI.h"

// Four In A Row
#include "FourInARow/FourInARow_Board.h"
#include "FourInARow/FourInARow_UI.h"

using namespace std;

// Function declarations
void run_sus_game();
void run_four_in_a_row_game();
void run_5x5_ttt_game();
void run_word_ttt_game();
void run_misere_ttt_game();
void run_diamond_ttt_game();
void run_4x4_ttt_game();
void run_pyramid_ttt_game();
void run_numerical_ttt_game();
void run_obstacles_ttt_game();
void run_infinity_ttt_game();

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    do {
        cout << "\n========================================\n";
        cout << "        Board Game Collection\n";
        cout << "========================================\n";
        cout << "1.  SUS\n";
        cout << "2.  Four in a Row\n";
        cout << "3.  5 x 5 Tic-Tac-Toe\n";
        cout << "4.  Word Tic-Tac-Toe\n";
        cout << "5.  Misere Tic-Tac-Toe\n";
        cout << "6.  Diamond Tic-Tac-Toe\n";
        cout << "7.  4 x 4 Tic-Tac-Toe\n";
        cout << "8.  Pyramid Tic-Tac-Toe\n";
        cout << "9.  Numerical Tic-Tac-Toe\n";
        cout << "10. Obstacles Tic-Tac-Toe\n";
        cout << "11. Infinity Tic-Tac-Toe\n";
        cout << "12. Random Game\n";
        cout << "0.  Exit\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice) {
            case 0: 
                cout << "\n---- Exiting Game Center ----\nHave a great day!\n"; 
                break;
            case 1: 
                run_sus_game(); 
                break;
            case 2:
                run_four_in_a_row_game();
                break;
            case 3:
                run_5x5_ttt_game();
                break;
            case 4:
                run_word_ttt_game();
                break;
            case 5:
                run_misere_ttt_game();
                break;
            case 6:
                run_diamond_ttt_game();
                break;
            case 7:
                run_4x4_ttt_game();
                break;
            case 8:
                run_pyramid_ttt_game();
                break;
            case 9:
                run_numerical_ttt_game(); 
                break;
            case 10:
                run_obstacles_ttt_game();
                break;
            case 11:
                run_infinity_ttt_game();
                break;
            case 12:
            {
                int random_game = rand() % 11 + 1; // Random number between 1 and 11
                cout << "Randomly selected game: " << random_game << endl;
                switch (random_game) {
                    case 1: run_sus_game(); break;
                    case 2: run_four_in_a_row_game(); break;
                    case 3: run_5x5_ttt_game(); break;
                    case 4: run_word_ttt_game(); break;
                    case 5: run_misere_ttt_game(); break;
                    case 6: run_diamond_ttt_game(); break;
                    case 7: run_4x4_ttt_game(); break;
                    case 8: run_pyramid_ttt_game(); break;
                    case 9: run_numerical_ttt_game(); break;
                    case 10: run_obstacles_ttt_game(); break;
                    case 11: run_infinity_ttt_game(); break;
                    }
                    break;
            }
            default:
                cout << "Invalid choice. Please select from menu (0-12)\n"; 
                break;
        }
    } while (choice != 0);
}

// ---------------------------------------------------------------

void run_sus_game() {
    cout << "\n---- Starting SUS Game ----\n";
    
    UI<char>* ui = new SUS_UI();
    Board<char>* board = new SUS_Board();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    static_cast<SUS_UI*>(ui)->show_score(static_cast<SUS_Board*>(board));
    cout << "\nThank You For Playing!\n--------------------------------\n"; 
    
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_four_in_a_row_game(){
    cout << "\n---- Starting Four In A Row ----\n";
    
    UI<char>* ui = new FourInARow_UI();
    Board<char>* board = new FourInARow_Board();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    cout << "\nThank You For Playing!\n--------------------------------\n"; 
    
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_5x5_ttt_game(){
    cout << "\n---- Starting 5x5 Tic-Tac-Toe ----\n";
    
    UI<char>* ui = new TTT5x5_UI();
    Board<char>* board = new TTT5x5_Board();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    static_cast<SUS_UI*>(ui)->show_score(static_cast<SUS_Board*>(board));
    cout << "\nThank You For Playing!\n--------------------------------\n"; 
    
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_word_ttt_game() {
    cout << "\n---- Starting Word Tic-Tac-Toe ----\n";

    UI<char>* ui = new WordTTT_UI();
    Board<char>* board = new WordTTT_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();
    static_cast<WordTTT_UI*>(ui)->show_score(static_cast<WordTTT_Board*>(board));
    cout << "\nThank You For Playing!\n--------------------------------\n"; 

    
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_misere_ttt_game() {
    cout << "\n---- Starting Standard Tic-Tac-Toe ----\n"; 
    
    UI<char>* ui = new TTT_UI();            
    Board<char>* board = new TTT_Board();   
    Player<char>** players = ui->setup_players(); 
    GameManager<char> game(board, players, ui);
    game.run();
    cout << "\nThank You For Playing!\n--------------------------------\n"; 

    
    delete board;                           
    delete ui;                              
    delete players[0];
    delete players[1];                 
    delete[] players;                      
}

void run_diamond_ttt_game(){
    cout << "Coming Soon!\n";
    cout << "Valid Games: 1, 4, 5, 8, 9, 10\n";
}

void run_4x4_ttt_game(){
    cout << "Coming Soon!\n";
    cout << "Valid Games: 1, 4, 5, 8, 9, 10\n";
}

void run_pyramid_ttt_game() {
    cout << "\n---- Starting Pyramid Tic-Tac-Toe ----\n";
    
    UI<char>* ui = new PyramidTTT_UI();
    Board<char>* board = new PyramidTTT_Board();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    cout << "\nThank You For Playing!\n--------------------------------\n";
    
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void run_numerical_ttt_game() {
    cout << "\n---- Starting Numerical Tic-Tac-Toe ----\n";
    
    UI<int>* ui = new NumericalTTT_UI();
    Board<int>* board = new NumericalTTT_Board();
    Player<int>** players = ui->setup_players();
    GameManager<int> game(board, players, ui);
    game.run();
    cout << "\nThank You For Playing!\n--------------------------------\n";

    delete board;
    delete ui;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}

void run_obstacles_ttt_game(){
    cout << "\n---- Starting Obstacles Tic-Tac-Toe ----\n";
    UI<char>* ui = new ObstaclesTTT_UI();
    Board<char>* board = new ObstaclesTTT_Board();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    cout << "\nThank You For Playing!\n--------------------------------\n";

    delete board;                           
    delete ui;                              
    for (int i = 0; i < 2; ++i) {
        delete players[i];                 
    }
    delete[] players; 
}

void run_infinity_ttt_game(){
    cout << "Coming Soon!\n";
    cout << "Valid Games: 1, 4, 5, 8, 9, 10\n";
}