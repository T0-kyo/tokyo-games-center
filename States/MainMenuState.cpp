#include <iostream>
#include <sstream>
#include "MainMenuState.h"
#include "ModeSelectionState.h"


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

        this->_WordTTT = std::make_unique<sf::Text> ( texture2, "Word Tic-Tac-Toe", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect1 = this->_WordTTT->getLocalBounds();


        this->_background->setPosition({SCREEN_WIDTH / 2 - texture1.getSize().x * 0.5f, SCREEN_HEIGHT / 2 - texture1.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 180 ) );
        this->_title->setFillColor( sf::Color(225, 165, 35) );
        this->_title->setPosition({ SCREEN_WIDTH /2 - textRect.size.x * 0.5f , SCREEN_HEIGHT * 0.075f});
        this->_WordTTT->setFillColor( sf::Color(225, 165, 35) );
        this->_WordTTT->setPosition({ SCREEN_WIDTH /2 - textRect.size.x * 0.5f , SCREEN_HEIGHT * 0.5f - textRect1.size.y});
    }

    void MainMenuState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if ( this->_data->input.isTextClicked( *this->_WordTTT, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Word)), false);
            }
        }
    }
        
    void MainMenuState::Update ( float dt ) {
        if (this->_data->input.hoverText( *this->_WordTTT, this->_data->window )) {
            this->_WordTTT->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_WordTTT->setFillColor( sf::Color(225, 165, 35) );
        }
    }
        
    void MainMenuState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_title );
        this->_data->window.draw( *this->_WordTTT );

        this->_data->window.display();
    }
}