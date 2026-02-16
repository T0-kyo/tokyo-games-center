#include "UltimateState.h"


namespace Tokyo {

    UltimateState::UltimateState ( GameDataRef data , PlayerType playerType ) : _data( data ) {}

    void UltimateState::Init() {
        std::cout << "UltimateState Init" << std::endl;
    }

    void UltimateState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void UltimateState::Update ( float dt ) {}

    void UltimateState::Draw ( float dt ) {
            this->_data->window.clear( sf::Color::Black );
            this->_data->window.display();
    }
}