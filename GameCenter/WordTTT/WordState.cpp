#include "WordState.h"


namespace Tokyo {

    WordState::WordState ( GameDataRef data, PlayerType playerType ) : _data( data ) {
        std::cout << "WordState Constructor" << std::endl;
    }

    void WordState::Init() {
        std::cout << "WordState Init" << std::endl;
    }

    void WordState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void WordState::Update( float dt ) {}

    void WordState::Draw( float dt ) {}
}