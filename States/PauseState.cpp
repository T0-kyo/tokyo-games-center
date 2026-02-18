#include "PauseState.h"

namespace Tokyo{

    PauseState::PauseState( GameDataRef data ) : _data( data ){}

    void PauseState::Init(){
        this->_data->assets.LoadTexture( "PauseBG", "../Assets/Textures/Game Background.jpg" );
        this->_data->assets.LoadTexture( "Resume", "../Assets/Textures/Resume Button.png" );
        this->_data->assets.LoadTexture( "Home", "../Assets/Textures/Home Button.png" );

        auto& bg = this->_data->assets.GetTexture("PauseBG");
        auto& res = this->_data->assets.GetTexture("Resume");
        auto& hm = this->_data->assets.GetTexture("Home");

        this->_background = std::make_unique<sf::Sprite>(bg);
        this->_resume = std::make_unique<sf::Sprite>(res);
        this->_home = std::make_unique<sf::Sprite>(hm);

        this->_background->setPosition({SCREEN_WIDTH / 2 - bg.getSize().x*0.5f, SCREEN_HEIGHT / 2 - bg.getSize().y*0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 70));

        this->_resume->setPosition({SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - res.getSize().y*0.5f});
        this->_resume->setColor(sf::Color(255, 255, 255, 150));

        this->_home->setPosition({SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - hm.getSize().y*0.5f});
        this->_home->setColor(sf::Color(255, 255, 255, 150));
    }

    void PauseState::HandleInput(){
        while(auto event = this->_data->window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                this->_data->window.close();
            }
            if(this->_data->input.isSpriteClicekd(*this->_resume, sf::Mouse::Button::Left, this->_data->window)){
                this->_data->machine.RemoveState();
            }
            if(this->_data->input.isSpriteClicekd(*this->_home, sf::Mouse::Button::Left, this->_data->window)){
                this->_data->machine.RemoveState();
                this->_data->machine.RemoveState();
            }
        }
    }

    void PauseState::Update(float dt){
        if(this->_data->input.hoverSprite(*this->_resume, this->_data->window)){
            this->_resume->setColor(sf::Color(255, 255, 255, 255));
        }
        else this->_resume->setColor(sf::Color(255, 255, 255, 150));

        if(this->_data->input.hoverSprite(*this->_home, this->_data->window)){
            this->_home->setColor(sf::Color(255, 255, 255, 255));
        }
        else this->_home->setColor(sf::Color(255, 255, 255, 150));
    }

    void PauseState::Draw(float dt){
        this->_data->window.clear();

        this->_data->window.draw(*this->_background);
        this->_data->window.draw(*this->_resume);
        this->_data->window.draw(*this->_home);

        this->_data->window.display();
    }
}