#include <iostream>
#include <sstream>
#include "SplashState.h"
#include "../DEFENITIONS.h"

namespace Tokyo {

    SplashState::SplashState ( GameDataRef data ) : _data( data ) {}

    void SplashState::Init() {
        this->_data->assets.LoadTexture( "Splash State Background", SPLASH_BACKGROUND_FILEPATH );
        auto& texture = this->_data->assets.GetTexture( "Splash State Background" );
        this->_background = std::make_unique<sf::Sprite> ( texture );
    }

    void SplashState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void SplashState::Update( float dt ) {
        if ( this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME ) {
            std::cout << "GO to Main Menu" << std::endl;
        }
    }

    void SplashState::Draw( float dt ) {
        this->_data->window.clear();
        this->_data->window.draw( *this->_background );
        this->_data->window.display();
    }
}