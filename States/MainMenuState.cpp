#include <iostream>
#include <sstream>
#include "MainMenuState.h"
#include "ModeSelectionState.h"


namespace Tokyo {

    MainMenuState::MainMenuState ( GameDataRef data ) : _data( data ) {}

    void MainMenuState::Init() {

        auto& texture1 = this->_data->assets.GetTexture( "Main Background" );
        this->_background = std::make_unique<sf::Sprite> ( texture1 );

        this->_data->assets.LoadTexture("numerical", "../Assets/Textures/numerical-ttt.png");
        this->_data->assets.LoadTexture("4x4", "../Assets/Textures/4x4.png");
        this->_data->assets.LoadTexture("5x5", "../Assets/Textures/5x5.png");
        this->_data->assets.LoadTexture("obstacles", "../Assets/Textures/obstacles.png");
        this->_data->assets.LoadTexture("pyramid", "../Assets/Textures/pyramid.png");
        this->_data->assets.LoadTexture("connect4", "../Assets/Textures/connect4.png");
        this->_data->assets.LoadTexture("diamond", "../Assets/Textures/diamond.png");
        this->_data->assets.LoadTexture("ultimate", "../Assets/Textures/ultimate.png");
        this->_data->assets.LoadTexture("memory", "../Assets/Textures/memory.png");
        this->_data->assets.LoadTexture("misere", "../Assets/Textures/misere.png");
        this->_data->assets.LoadTexture("infinity", "../Assets/Textures/infinity.png");
        this->_data->assets.LoadTexture("sus", "../Assets/Textures/sus.png");
        this->_data->assets.LoadTexture("word", "../Assets/Textures/word.png");
        
        auto& numerical = this->_data->assets.GetTexture( "numerical" );
        auto& fourxfour = this->_data->assets.GetTexture( "4x4" );
        auto& fivexfive = this->_data->assets.GetTexture( "5x5" );
        auto& obstacles = this->_data->assets.GetTexture( "obstacles" );
        auto& pyramid = this->_data->assets.GetTexture( "pyramid" );
        auto& connect4 = this->_data->assets.GetTexture( "connect4" );
        auto& diamond = this->_data->assets.GetTexture( "diamond" );
        auto& memory = this->_data->assets.GetTexture( "memory" );
        auto& misere = this->_data->assets.GetTexture( "misere" );
        auto& sus = this->_data->assets.GetTexture( "sus" );
        auto& ultimate = this->_data->assets.GetTexture( "ultimate" );
        auto& word = this->_data->assets.GetTexture( "word" );
        auto& infinity = this->_data->assets.GetTexture( "infinity" );
        
        this->_4x4TTT_Button = std::make_unique<sf::Sprite> ( fourxfour );
        this->_5x5TTT_Button = std::make_unique<sf::Sprite> ( fivexfive );
        this->_NumericalTTT_Button = std::make_unique<sf::Sprite> ( numerical );
        this->_PyramidTTT_Button = std::make_unique<sf::Sprite> ( pyramid );
        this->_ObstaclesTTT_Button = std::make_unique<sf::Sprite> ( obstacles );
        this->_FourInARow_Button = std::make_unique<sf::Sprite> ( connect4 );
        this->_DiamondTTT_Button = std::make_unique<sf::Sprite> (diamond);
        this->_MemoryTTT_Button = std::make_unique<sf::Sprite> (memory);
        this->_MisereTTT_Button = std::make_unique<sf::Sprite> (misere);
        this->_SUS_Button = std::make_unique<sf::Sprite> (sus);
        this->_UltimateTTT_Button = std::make_unique<sf::Sprite> (ultimate);
        this->_WordTTT_Button = std::make_unique<sf::Sprite> (word);
        this->_InfinityTTT_Button = std::make_unique<sf::Sprite> (infinity);
        
        auto& font = this->_data->assets.GetFont( "Main Font" );
        this->_title = std::make_unique<sf::Text> ( font, "Game Center", MAIN_MENU_TITLE_SIZE );
        sf::FloatRect textRect = this->_title->getLocalBounds();
        
        this->_WordTTT_Button = std::make_unique<sf::Sprite> ( word );
        this->_UltimateTTT_Button = std::make_unique<sf::Sprite> ( ultimate );
        this->_SUS_Button = std::make_unique<sf::Sprite> ( sus );
        this->_PyramidTTT_Button = std::make_unique<sf::Sprite> ( pyramid );
        this->_ObstaclesTTT_Button = std::make_unique<sf::Sprite> ( obstacles );
        this->_NumericalTTT_Button = std::make_unique<sf::Sprite> ( numerical );
        this->_MisereTTT_Button = std::make_unique<sf::Sprite> ( misere );
        this->_MemoryTTT_Button = std::make_unique<sf::Sprite> ( memory );
        this->_InfinityTTT_Button = std::make_unique<sf::Sprite> ( infinity );
        this->_FourInARow_Button = std::make_unique<sf::Sprite> ( connect4 );
        this->_DiamondTTT_Button = std::make_unique<sf::Sprite> ( diamond );
        this->_5x5TTT_Button = std::make_unique<sf::Sprite> ( fivexfive );
        this->_4x4TTT_Button = std::make_unique<sf::Sprite> ( fourxfour );

        this->_background->setPosition({SCREEN_WIDTH / 2 - texture1.getSize().x * 0.5f, SCREEN_HEIGHT / 2 - texture1.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 180 ) );
        this->_title->setFillColor( sf::Color(225, 165, 35) );
        this->_title->setPosition({ SCREEN_WIDTH /2 - textRect.size.x * 0.5f , SCREEN_HEIGHT * 0.075f});

        this->_SUS_Button->setColor( sf::Color(225, 165, 35) );
        this->_SUS_Button->setPosition({157 + 50, 250}); //TODO Non professional way of centering the icons
        
        this->_5x5TTT_Button->setColor(sf::Color(255, 255, 255));
        this->_5x5TTT_Button->setPosition({489 + 50, 250});

        this->_WordTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_WordTTT_Button->setPosition({821 + 50, 250});

        this->_UltimateTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_UltimateTTT_Button->setPosition({1153 + 50, 250});

        //this->_NumericalTTT_Button->setColor(sf::Color(255, 255, 255));
        this->_NumericalTTT_Button->setPosition({102 + 50, 450});

        this->_PyramidTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_PyramidTTT_Button->setPosition({379 + 50, 450});

        this->_ObstaclesTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_ObstaclesTTT_Button->setPosition({656 + 50, 450});

        this->_MisereTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_MisereTTT_Button->setPosition({933 + 50, 450});

        this->_MemoryTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_MemoryTTT_Button->setPosition({1210 + 50, 450});

        this->_InfinityTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_InfinityTTT_Button->setPosition({157 + 50, 650});

        this->_FourInARow_Button->setColor( sf::Color(225, 165, 35) );
        this->_FourInARow_Button->setPosition({489 + 50, 650});

        this->_DiamondTTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_DiamondTTT_Button->setPosition({821 + 50, 650});

        this->_4x4TTT_Button->setColor( sf::Color(225, 165, 35) );
        this->_4x4TTT_Button->setPosition({1153 + 50, 650}); //TODO
    }

    void MainMenuState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if ( this->_data->input.isSpriteClicked( *this->_WordTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Word)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_UltimateTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Ultimate)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_SUS_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Sus)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_PyramidTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Pyramid)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_ObstaclesTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Obstacles)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_NumericalTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Numerical)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_MisereTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Misere)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_MemoryTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Memory)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_InfinityTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Infinity)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_FourInARow_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::FourInARow)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_DiamondTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Diamond)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_5x5TTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::_5x5)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_4x4TTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::_4x4)), false);
            }
        }
    }
        
    void MainMenuState::Update ( float dt ) {
        if (this->_data->input.hoverSprite( *this->_WordTTT_Button, this->_data->window )) {
            this->_WordTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_WordTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_UltimateTTT_Button, this->_data->window )) {
            this->_UltimateTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_UltimateTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_SUS_Button, this->_data->window )) {
            this->_SUS_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_SUS_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_PyramidTTT_Button, this->_data->window )) {
            this->_PyramidTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_PyramidTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_ObstaclesTTT_Button, this->_data->window )) {
            this->_ObstaclesTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_ObstaclesTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_NumericalTTT_Button, this->_data->window )) {
            this->_NumericalTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_NumericalTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_MisereTTT_Button, this->_data->window )) {
            this->_MisereTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_MisereTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_MemoryTTT_Button, this->_data->window )) {
            this->_MemoryTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_MemoryTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_InfinityTTT_Button, this->_data->window )) {
            this->_InfinityTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_InfinityTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_FourInARow_Button, this->_data->window )) {
            this->_FourInARow_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_FourInARow_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_DiamondTTT_Button, this->_data->window )) {
            this->_DiamondTTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_DiamondTTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_5x5TTT_Button, this->_data->window )) {
            this->_5x5TTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_5x5TTT_Button->setColor( sf::Color(225, 255, 255, 255) );
        }

        if (this->_data->input.hoverSprite( *this->_4x4TTT_Button, this->_data->window )) {
            this->_4x4TTT_Button->setColor( sf::Color(255, 255, 255, 150) );
        }
        else {
            this->_4x4TTT_Button->setColor( sf::Color(225, 255, 255, 255) );
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