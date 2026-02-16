#include "SUSState.h"


namespace Tokyo {

    SusState::SusState ( GameDataRef data , PlayerType playerType ) : _data( data ) {}

    void SusState::Init() {
        std::cout << "SUS State Init" << std::endl;
    }

    void SusState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void SusState::Update ( float dt ) {}

    void SusState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
            this->_data->window.display();
    }
}