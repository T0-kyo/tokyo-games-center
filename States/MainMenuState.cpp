#include <iostream>
#include <sstream>
#include "MainMenuState.h"
#include "ModeSelectionState.h"


namespace Tokyo {

    MainMenuState::MainMenuState ( GameDataRef data ) : _data( data ) {}

    void MainMenuState::Init() {

        auto& texture1 = this->_data->assets.GetTexture( "Main Background" );
        this->_background = std::make_unique<sf::Sprite> ( texture1 );

        this->_data->assets.LoadTexture("logo", "../Assets/Textures/logo-test1.png");
        this->_data->assets.LoadTexture("sound on", "../Assets/Textures/Sound On.png");
        this->_data->assets.LoadTexture("sound off", "../Assets/Textures/Sound Off.png");
        this->_data->assets.LoadTexture("numerical", "../Assets/Textures/numerical.png");
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
        this->_data->assets.LoadSound("choice", "../Assets/Audio/action-sound.wav");
        
        auto& logo = this->_data->assets.GetTexture( "logo" );
        auto& soundOn = this->_data->assets.GetTexture( "sound on" );
        auto& soundOff = this->_data->assets.GetTexture( "sound off" );
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
        auto& choose = this->_data->assets.GetSound( "choice" );

        this->_logo = std::make_unique<sf::Sprite> ( logo );
        this->_soundOn = std::make_unique<sf::Sprite> ( soundOn );
        this->_soundOff = std::make_unique<sf::Sprite> ( soundOff );
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
        this->_choose = std::make_unique<sf::Sound> ( choose );

        this->_background->setPosition({SCREEN_WIDTH / 2 - texture1.getSize().x * 0.5f, SCREEN_HEIGHT / 2 - texture1.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 200 ) );

        this->_logo->setPosition({SCREEN_WIDTH / 2.0f - logo.getSize().x / 2.0f, SCREEN_HEIGHT * 0.03f});

        this->_soundOn->setPosition({SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.04f});
        this->_soundOff->setPosition({SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.04f});

        this->_NumericalTTT_Button->setPosition({304, 240}); //TODO Non professional way of centering the icons
        this->_5x5TTT_Button->setPosition({564, 240});
        this->_WordTTT_Button->setPosition({824, 240});
        this->_UltimateTTT_Button->setPosition({1084, 240}); //* line 1
        this->_FourInARow_Button->setPosition({214, 470});
        this->_PyramidTTT_Button->setPosition({454, 470});
        this->_ObstaclesTTT_Button->setPosition({694, 470});
        this->_MisereTTT_Button->setPosition({934, 470});
        this->_MemoryTTT_Button->setPosition({1174, 470}); //* line 2
        this->_InfinityTTT_Button->setPosition({304, 700});
        this->_SUS_Button->setPosition({564, 700});
        this->_DiamondTTT_Button->setPosition({824, 700});
        this->_4x4TTT_Button->setPosition({1084, 700}); //TODO

    }

    void MainMenuState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if ( this->_data->input.isSpriteClicked( *this->_WordTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Word, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_UltimateTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Ultimate, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_SUS_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Sus, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_PyramidTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Pyramid, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_ObstaclesTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Obstacles, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_NumericalTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Numerical, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_MisereTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Misere, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_MemoryTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Memory, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_InfinityTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Infinity, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_FourInARow_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::FourInARow, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_DiamondTTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::Diamond, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_5x5TTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::_5x5, _isMute)), false);
            }

            if ( this->_data->input.isSpriteClicked( *this->_4x4TTT_Button, sf::Mouse::Button::Left, this->_data->window ) ) {
                this->_data->_delay.restart();
                if(!_isMute) this->_choose->play();
                this->_data->machine.AddState(StateRef(new ModeSelectionState(this->_data, GameID::_4x4, _isMute)), false);
            }

            if( this->_data->input.isSpriteClicked( *this->_soundOn, sf::Mouse::Button::Left, this->_data->window ) ) {
                if(!_isMute) this->_choose->play();
                this->_isMute = 1 - _isMute;
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

        if (this->_data->input.hoverSprite( *this->_soundOn, this->_data->window )) {
            this->_soundOn->setColor( sf::Color(255, 255, 255, 255) );
        }
        else {
            this->_soundOn->setColor( sf::Color(225, 255, 255, 150) );
        }

        if (this->_data->input.hoverSprite( *this->_soundOff, this->_data->window )) {
            this->_soundOff->setColor( sf::Color(255, 255, 255, 255) );
        }
        else {
            this->_soundOff->setColor( sf::Color(225, 255, 255, 150) );
        }
    }
        
    void MainMenuState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_logo );
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

        if(!_isMute) this->_data->window.draw( *this->_soundOn );
        else this->_data->window.draw( *this->_soundOff );

        this->_data->window.display();
    }
}