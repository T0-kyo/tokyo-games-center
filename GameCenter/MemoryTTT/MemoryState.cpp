#include "MemoryState.h"


namespace Tokyo {

    MemoryState::MemoryState ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void MemoryState::Init() {
        std::cout << "MemoryState Init" << std::endl;
    }

    void MemoryState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void MemoryState::Update ( float dt ) {}
        
    void MemoryState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }

}