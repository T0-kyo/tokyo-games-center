#ifndef TTT_UI_H                    
#define TTT_UI_H                      

#include "../BoardGameFramework/BoardGame_Classes.h" 
#include <iostream>                  
#include <string>                     

using namespace std;                

class TTT_UI : public UI<char> {
public:
    TTT_UI();                        

    virtual Player<char>** setup_players() override;
    
    virtual Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    
    virtual Move<char>* get_move(Player<char>* player) override;
};

#endif 