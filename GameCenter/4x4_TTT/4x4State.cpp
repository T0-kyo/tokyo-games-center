#include "4x4State.h"


namespace Tokyo {

    State4x4::State4x4 ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void State4x4::Init() {
        std::cout << "4x4 State Init" << std::endl;
    }

    void State4x4::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void State4x4::Update ( float dt ) {}
        
    void State4x4::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }

}