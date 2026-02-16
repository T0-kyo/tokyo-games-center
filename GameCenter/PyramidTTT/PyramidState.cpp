#include "PyramidState.h"


namespace Tokyo {

    PyramidState::PyramidState ( GameDataRef data , PlayerType playerType ) : _data( data ) {}

    void PyramidState::Init() {
        std::cout << "PyramidState Init" << std::endl;
    }

    void PyramidState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void PyramidState::Update ( float dt ) {}

    void PyramidState::Draw ( float dt ) {
        this->_data->window.clear(sf::Color::Black);
        this->_data->window.display();
    }
}