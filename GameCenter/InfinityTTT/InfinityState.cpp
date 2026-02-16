#include "InfinityState.h"


namespace Tokyo {

    InfinityState::InfinityState ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void InfinityState::Init() {
        std::cout << "Initializing Infinity State" << std::endl;
    }

    void InfinityState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void InfinityState::Update ( float dt ) {}
        
    void InfinityState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }

}