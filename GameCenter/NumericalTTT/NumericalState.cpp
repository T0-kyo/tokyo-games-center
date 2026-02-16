#include "NumericalState.h"


namespace Tokyo {

    NumericalState::NumericalState ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void NumericalState::Init() {
        std::cout << "Numerical Tic Tac Toe State Initialized" << std::endl;
    }

    void NumericalState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void NumericalState::Update ( float dt ) {}

    void NumericalState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();  
    }
}