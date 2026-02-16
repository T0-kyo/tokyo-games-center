#include "ObstaclesState.h"


namespace Tokyo {

    ObstaclesState::ObstaclesState ( GameDataRef data , PlayerType playerType ) : _data( data ) {}

    void ObstaclesState::Init() {
        std::cout << "ObstaclesState Init" << std::endl;
    }

    void ObstaclesState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void ObstaclesState::Update ( float dt ) {}

    void ObstaclesState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }
}