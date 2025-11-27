#include "MisereTTT_UI.h"                  
#include <limits>                     
TTT_UI::TTT_UI() : UI("Welcome to Standard Tic-Tac-Toe! (3x3)", 1) {}


Player<char>** TTT_UI::setup_players() {
    
    Player<char>** players = new Player<char>*[2];
    
    
    vector<string> type_options = { "Human", "Computer" };

    
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


Player<char>* TTT_UI::create_player(string& name, char symbol, PlayerType type) {
    
    return new Player<char>(name, symbol, type);
}


Move<char>* TTT_UI::get_move(Player<char>* player) {
    int x, y;                         
    char symbol = player->get_symbol(); 

    cout << "\n" << player->get_name() << " (" << symbol << ") turn.\n"; 

   
    if (player->get_type() == PlayerType::COMPUTER) {
       
        Board<char>* board = player->get_board_ptr(); 
        
       
        do {
            x = rand() % 3;          
            y = rand() % 3;          
        } while (board->get_board_matrix()[x][y] != ' '); 
        
        cout << "Computer chose: " << x << " " << y << endl; 
        return new Move<char>(x, y, symbol);
    }

   
    while (true) {
        cout << "Enter row (0-2) and column (0-2) separated by space: "; 
        
        
        if (cin >> x >> y) {
            
            if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
                
                Board<char>* board = player->get_board_ptr();
                if (board->get_board_matrix()[x][y] == ' ') {
                   break; 
                } else {
                   cout << "Cell is already occupied!\n";
                }
            } else {
                cout << "Invalid coordinates! Use 0 to 2.\n";
            }
        } else {
            
            cin.clear();             
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter numbers.\n";
        }
    }

    return new Move<char>(x, y, symbol); 
}