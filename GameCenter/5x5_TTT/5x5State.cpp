#include "5x5State.h"


namespace Tokyo {

    State5x5::State5x5 ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void State5x5::Init() {
        std::cout << "5x5 State Init" << std::endl;
    }

    void State5x5::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void State5x5::Update ( float dt ) {}
        
    void State5x5::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }

}