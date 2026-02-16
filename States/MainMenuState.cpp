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

        this->_WordTTT_Button = std::make_unique<sf::Text> ( texture2, "Word", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect1 = this->_WordTTT_Button->getLocalBounds();

        this->_UltimateTTT_Button = std::make_unique<sf::Text> ( texture2, "Ultimate", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect2 = this->_UltimateTTT_Button->getLocalBounds();

        this->_SUS_Button = std::make_unique<sf::Text> ( texture2, "SUS", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect3 = this->_SUS_Button->getLocalBounds();

        this->_PyramidTTT_Button = std::make_unique<sf::Text> ( texture2, "Pyramid", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect4 = this->_PyramidTTT_Button->getLocalBounds();

        this->_ObstaclesTTT_Button = std::make_unique<sf::Text> ( texture2, "Obstacles", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect5 = this->_ObstaclesTTT_Button->getLocalBounds();

        this->_NumericalTTT_Button = std::make_unique<sf::Text> ( texture2, "Numerical", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect6 = this->_NumericalTTT_Button->getLocalBounds();

        this->_MisereTTT_Button = std::make_unique<sf::Text> ( texture2, "Misere", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect7 = this->_MisereTTT_Button->getLocalBounds();

        this->_MemoryTTT_Button = std::make_unique<sf::Text> ( texture2, "Memory", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect8 = this->_MemoryTTT_Button->getLocalBounds();

        this->_InfinityTTT_Button = std::make_unique<sf::Text> ( texture2, "Infinity", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect9 = this->_InfinityTTT_Button->getLocalBounds();

        this->_FourInARow_Button = std::make_unique<sf::Text> ( texture2, "Four in a row", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect10 = this->_FourInARow_Button->getLocalBounds();

        this->_DiamondTTT_Button = std::make_unique<sf::Text> ( texture2, "Diamond", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect11 = this->_DiamondTTT_Button->getLocalBounds();

        this->_5x5TTT_Button = std::make_unique<sf::Text> ( texture2, "5x5", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect12 = this->_5x5TTT_Button->getLocalBounds();

        this->_4x4TTT_Button = std::make_unique<sf::Text> ( texture2, "4x4", MAIN_MENU_TITLE_SIZE / 3 );
        sf::FloatRect textRect13 = this->_4x4TTT_Button->getLocalBounds();


        this->_background->setPosition({SCREEN_WIDTH / 2 - texture1.getSize().x * 0.5f, SCREEN_HEIGHT / 2 - texture1.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 180 ) );
        this->_title->setFillColor( sf::Color(225, 165, 35) );
        this->_title->setPosition({ SCREEN_WIDTH /2 - textRect.size.x * 0.5f , SCREEN_HEIGHT * 0.075f});

        this->_WordTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_WordTTT_Button->setPosition({ SCREEN_WIDTH /2 - textRect6.size.x * 2.5f , SCREEN_HEIGHT * 0.5f - textRect.size.y * 2.0f});
        
        this->_UltimateTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_UltimateTTT_Button->setPosition({ SCREEN_WIDTH /2 - textRect6.size.x * 0.75f , SCREEN_HEIGHT * 0.5f - textRect.size.y * 2.0f});

        this->_SUS_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_SUS_Button->setPosition({ SCREEN_WIDTH /2 + textRect6.size.x * 0.75f , SCREEN_HEIGHT * 0.5f - textRect.size.y * 2.0f});

        this->_PyramidTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_PyramidTTT_Button->setPosition({ SCREEN_WIDTH /2 + textRect6.size.x * 2.5f , SCREEN_HEIGHT * 0.5f - textRect.size.y * 2.0f});

        this->_ObstaclesTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_ObstaclesTTT_Button->setPosition({ SCREEN_WIDTH /2 - textRect6.size.x * 2.5f , SCREEN_HEIGHT * 0.5f});

        this->_NumericalTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_NumericalTTT_Button->setPosition({ SCREEN_WIDTH /2 - textRect6.size.x * 0.75f , SCREEN_HEIGHT * 0.5f});

        this->_MisereTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_MisereTTT_Button->setPosition({ SCREEN_WIDTH /2 + textRect6.size.x * 0.75f , SCREEN_HEIGHT * 0.5f});

        this->_MemoryTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_MemoryTTT_Button->setPosition({ SCREEN_WIDTH /2 + textRect6.size.x * 2.5f , SCREEN_HEIGHT * 0.5f});

        this->_InfinityTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_InfinityTTT_Button->setPosition({ SCREEN_WIDTH /2 - textRect6.size.x * 2.5f , SCREEN_HEIGHT * 0.5f + textRect.size.y});

        this->_FourInARow_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_FourInARow_Button->setPosition({ SCREEN_WIDTH /2 - textRect10.size.x * 0.5f , SCREEN_HEIGHT * 0.5f + textRect.size.y * 2});

        this->_DiamondTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_DiamondTTT_Button->setPosition({ SCREEN_WIDTH /2 - textRect6.size.x * 0.75f , SCREEN_HEIGHT * 0.5f + textRect.size.y});

        this->_5x5TTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_5x5TTT_Button->setPosition({ SCREEN_WIDTH /2 + textRect6.size.x * 0.75f , SCREEN_HEIGHT * 0.5f + textRect.size.y});

        this->_4x4TTT_Button->setFillColor( sf::Color(225, 165, 35) );
        this->_4x4TTT_Button->setPosition({ SCREEN_WIDTH /2 + textRect6.size.x * 2.5f , SCREEN_HEIGHT * 0.5f + textRect.size.y});
    }

    void MainMenuState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if ( this->_data->input.isTextClicked( *this->_WordTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Word)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_UltimateTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Ultimate)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_SUS_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Sus)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_PyramidTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Pyramid)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_ObstaclesTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Obstacles)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_NumericalTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Numerical)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_MisereTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Misere)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_MemoryTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Memory)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_InfinityTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Infinity)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_FourInARow_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::FourInARow)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_DiamondTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Diamond)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_5x5TTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::_5x5)), false);
            }

            if ( this->_data->input.isTextClicked( *this->_4x4TTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::_4x4)), false);
            }
        }
    }
        
    void MainMenuState::Update ( float dt ) {
        if (this->_data->input.hoverText( *this->_WordTTT_Button, this->_data->window )) {
            this->_WordTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_WordTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_UltimateTTT_Button, this->_data->window )) {
            this->_UltimateTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_UltimateTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_SUS_Button, this->_data->window )) {
            this->_SUS_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_SUS_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_PyramidTTT_Button, this->_data->window )) {
            this->_PyramidTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_PyramidTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_ObstaclesTTT_Button, this->_data->window )) {
            this->_ObstaclesTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_ObstaclesTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_NumericalTTT_Button, this->_data->window )) {
            this->_NumericalTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_NumericalTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_MisereTTT_Button, this->_data->window )) {
            this->_MisereTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_MisereTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_MemoryTTT_Button, this->_data->window )) {
            this->_MemoryTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_MemoryTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_InfinityTTT_Button, this->_data->window )) {
            this->_InfinityTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_InfinityTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_FourInARow_Button, this->_data->window )) {
            this->_FourInARow_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_FourInARow_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_DiamondTTT_Button, this->_data->window )) {
            this->_DiamondTTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_DiamondTTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_5x5TTT_Button, this->_data->window )) {
            this->_5x5TTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_5x5TTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }

        if (this->_data->input.hoverText( *this->_4x4TTT_Button, this->_data->window )) {
            this->_4x4TTT_Button->setFillColor( sf::Color(255, 255, 255) );
        }
        else {
            this->_4x4TTT_Button->setFillColor( sf::Color(225, 165, 35) );
        }
    }
        
    void MainMenuState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_title );
        this->_data->window.draw( *this->_WordTTT_Button );
        this->_data->window.draw( *this->_UltimateTTT_Button );
        this->_data->window.draw( *this->_SUS_Button );
        this->_data->window.draw( *this->_PyramidTTT_Button );
        this->_data->window.draw( *this->_ObstaclesTTT_Button );
        this->_data->window.draw( *this->_NumericalTTT_Button );
        this->_data->window.draw( *this->_MisereTTT_Button );
        this->_data->window.draw( *this->_MemoryTTT_Button );
        this->_data->window.draw( *this->_InfinityTTT_Button );
        this->_data->window.draw( *this->_FourInARow_Button );
        this->_data->window.draw( *this->_DiamondTTT_Button );
        this->_data->window.draw( *this->_5x5TTT_Button );
        this->_data->window.draw( *this->_4x4TTT_Button );

        this->_data->window.display();
    }
}