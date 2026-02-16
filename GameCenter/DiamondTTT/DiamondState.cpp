#include "DiamondState.h"


namespace Tokyo {

    DiamondState::DiamondState ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void DiamondState::Init() {
        std::cout << "Diamond Tic-Tac-Toe State Initialized" << std::endl;
    }

    void DiamondState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void DiamondState::Update ( float dt ) {}

    void DiamondState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }
}