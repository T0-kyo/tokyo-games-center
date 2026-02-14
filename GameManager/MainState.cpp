#include <iostream>
#include <sstream>
#include "MainState.h"
#include "MainMenuState.h"


namespace Tokyo {

    MainState::MainState ( GameDataRef data ) : _data( data ) {}

    void MainState::Init() {

        this->_data->assets.LoadTexture( "Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH );
        this->_data->assets.LoadFont( "Start Button", MAIN_MENU_TITLE_FILEPATH );
        

        auto& texture1 = this->_data->assets.GetTexture( "Main Menu Background" );
        this->_background = std::make_unique<sf::Sprite> ( texture1 );

        
        auto& texture2 = this->_data->assets.GetFont( "Start Button" );
        this->_startButton = std::make_unique<sf::Text> ( texture2, "Start", MAIN_MENU_TITLE_SIZE );
        sf::FloatRect textRect = this->_startButton->getLocalBounds();

        this->_background->setPosition({SCREEN_WIDTH / 2 - texture1.getSize().x * 0.5f, SCREEN_HEIGHT / 2 - texture1.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 180 ) );
        this->_startButton->setFillColor( sf::Color(225, 165, 35) );
        this->_startButton->setPosition({ SCREEN_WIDTH /2 - textRect.size.x * 0.5f , SCREEN_HEIGHT * 0.45f});
    }

    void MainState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if ( this->_data->input.isTextClicked( *this->_startButton, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState ( StateRef ( new MainMenuState ( this->_data ) ) );
            }
        }
    }
        
    void MainState::Update ( float dt ) {
        if (this->_data->input.hoverText( *this->_startButton, this->_data->window )) {
            this->_startButton->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_startButton->setFillColor( sf::Color(225, 165, 35) );
        }
    }
        
    void MainState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_startButton );

        this->_data->window.display();
    }
}