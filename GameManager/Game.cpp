#include "Game.h"
#include "../States/SplashState.h"


namespace Tokyo {

    Game::Game ( unsigned int width, unsigned int height, string title )  {

        _data->window.create( sf::VideoMode( {width, height} ), title, sf::Style::Close | sf::Style::Titlebar );
        this->_data->window.setFramerateLimit(60);
        _data->machine.AddState( StateRef( new SplashState( this->_data ) ) );
        this->Run();
    }

    void Game::Run() {

        while (this->_data->window.isOpen()) {
            float frameTime = this->_clock.restart().asSeconds();
            this->_data->machine.ProcessStateChanges();

            if(this->_data->_delay.getElapsedTime().asSeconds() >= INPUT_DELAY){
                this->_data->machine.GetActiveState()->HandleInput();
            }
            else {
                while ( auto event = this->_data->window.pollEvent() ) {
                    if ( event->is<sf::Event::Closed>() ) {
                        this->_data->window.close();
                    }
                }   
            }

            this->_data->machine.GetActiveState()->Update( frameTime );
            this->_data->machine.GetActiveState()->Draw( frameTime );
        }
    }
}