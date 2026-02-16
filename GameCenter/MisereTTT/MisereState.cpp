#include "MisereState.h"


namespace Tokyo {

    MisereState::MisereState ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void MisereState::Init() {
        std::cout<< "Initializing Misere State" << std::endl;
    }

    void MisereState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void MisereState::Update ( float dt ) {}
        
    void MisereState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }

}