#include "GameOverState.h"


namespace Tokyo {
    GameOverState::GameOverState(GameDataRef data, GameID gameID, Winner winner) : _data(data), _gameID(gameID), _winner(winner) {}

    void GameOverState::Init(){}

    void GameOverState::HandleInput(){
        while(auto event = this->_data->window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                this->_data->window.close();
            }
        }
    }

    void GameOverState::Update( float dt ){}

    void GameOverState::Draw( float dt ){
        this->_data->window.clear(sf::Color::Black);
        this->_data->window.display();
    }
}