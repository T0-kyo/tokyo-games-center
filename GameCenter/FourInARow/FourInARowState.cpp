#include "FourInARowState.h"


namespace Tokyo {

    FourInARowState::FourInARowState ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void FourInARowState::Init() {
        std::cout << "Initializing Four In A Row State" << std::endl;
    }

    void FourInARowState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void FourInARowState::Update ( float dt ) {}
        
    void FourInARowState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }

}