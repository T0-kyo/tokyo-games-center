#include <iostream>
#include <sstream>
#include "SplashState.h"
#include "MainState.h"

namespace Tokyo {

    SplashState::SplashState ( GameDataRef data ) : _data( data ) {}

    void SplashState::Init() {
        this->_data->assets.LoadTexture( "Splash State Background", SPLASH_BACKGROUND_FILEPATH );
        auto& texture = this->_data->assets.GetTexture( "Splash State Background" );
        this->_background = std::make_unique<sf::Sprite> ( texture );
        this->_background->setPosition( { SCREEN_WIDTH*0.5f - texture.getSize().x*0.5f, SCREEN_HEIGHT*0.5f - texture.getSize().y*0.5f } );
        this->_background->setColor( sf::Color( 255, 255, 255, 0 ) );
    }

    void SplashState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void SplashState::Update(float dt)
{
    float fadeSpeed = 255.f / FADE_EFFECT_DURATION;
    elapsed += dt;

    if (elapsed < StartDelay)
    {
        return;
    }

    if (_phase == FadeState::FadeIn)
    {
        _alpha += fadeSpeed * dt;

        if (_alpha >= 255.f)
        {
            _alpha = 255.f;
            _phase = FadeState::Show;
            this->_clock.restart();
        }
    }

    else if (_phase == FadeState::Show)
    {
        if (this->_clock.getElapsedTime().asSeconds()
            >= SPLASH_STATE_SHOW_TIME)
        {
            _phase = FadeState::FadeOut;
        }
    }

    else if (_phase == FadeState::FadeOut)
    {
        _alpha -= fadeSpeed * dt;

        if (_alpha <= 0.f)
        {
            _alpha = 0.f;
            
            this->_background->setColor(
        sf::Color(255, 255, 255,static_cast<std::uint8_t>(_alpha)));
            
            this->_data->machine.AddState( StateRef( new MainState( this->_data ) ), true );
        }
    }

    this->_background->setColor(
        sf::Color(255, 255, 255,static_cast<std::uint8_t>(_alpha)));
}

    void SplashState::Draw( float dt ) {
        this->_data->window.clear(sf::Color(30, 30, 30));
        this->_data->window.draw( *this->_background );
        this->_data->window.display();
    }
}