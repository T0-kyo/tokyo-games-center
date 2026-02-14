#include <iostream>
#include <sstream>
#include "MainMenuState.h"


namespace Tokyo {

    MainMenuState::MainMenuState ( GameDataRef data ) : _data( data ) {}

    void MainMenuState::Init() {

        this->_data->assets.LoadTexture( "Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH );
        this->_data->assets.LoadFont( "Game Title", MAIN_MENU_TITLE_FILEPATH );
        

        auto& texture1 = this->_data->assets.GetTexture( "Main Menu Background" );
        this->_background = std::make_unique<sf::Sprite> ( texture1 );

        
        auto& texture2 = this->_data->assets.GetFont( "Game Title" );
        this->_title = std::make_unique<sf::Text> ( texture2, "Game Center", MAIN_MENU_TITLE_SIZE );
        sf::FloatRect textRect = this->_title->getLocalBounds();

        this->_background->setPosition({SCREEN_WIDTH / 2 - texture1.getSize().x * 0.5f, SCREEN_HEIGHT / 2 - texture1.getSize().y * 0.5f});
        this->_title->setFillColor( sf::Color(235, 185, 80) );
        this->_title->setPosition({ SCREEN_WIDTH /2 - textRect.size.x * 0.5f , SCREEN_HEIGHT*0.075f});
    }

    void MainMenuState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void MainMenuState::Update ( float dt ) {

    }
        
    void MainMenuState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_title );

        this->_data->window.display();
    }
}