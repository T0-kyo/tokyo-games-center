#include "HomeState.h"

namespace Tokyo{

    HomeState::HomeState( GameDataRef data ) : _data( data ){}

    void HomeState::Init(){
        this->_data->assets.LoadTexture( "HomeBG", "../Assets/Textures/MainBackground.png" );

        auto& bg = this->_data->assets.GetTexture("HomeBG");
        auto& text = this->_data->assets.GetFont( "Main Font" );

        this->_background = std::make_unique<sf::Sprite>(bg);

        this->_background->setPosition({SCREEN_WIDTH / 2 - bg.getSize().x*0.5f, SCREEN_HEIGHT / 2 - bg.getSize().y*0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 70));

        this->_yes = std::make_unique<sf::Text> ( text, "YES", MAIN_MENU_TITLE_SIZE / 1.5 );
        sf::FloatRect textRect1 = this->_yes->getLocalBounds();

        this->_no = std::make_unique<sf::Text> ( text, "NO", MAIN_MENU_TITLE_SIZE / 1.5 );
        sf::FloatRect textRect2 = this->_no->getLocalBounds();

        this->_quest = std::make_unique<sf::Text> ( text, "ARE YOU SURE TO LEAVE THE GAME?", MAIN_MENU_TITLE_SIZE / 2.2 );
        sf::FloatRect textRect3 = this->_quest->getLocalBounds();

        this->_quest->setFillColor( sf::Color(225, 0, 255) );
        this->_quest->setPosition({SCREEN_WIDTH / 2 - textRect3.size.x*0.5f, textRect3.size.y*3.5f});

        this->_yes->setFillColor( sf::Color(225, 0, 255) );
        this->_yes->setPosition({SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - textRect1.size.y*0.5f});

        this->_no->setFillColor( sf::Color(225, 0, 255) );
        this->_no->setPosition({SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - textRect2.size.y*0.5f});
    }

    void HomeState::HandleInput(){
        while(auto event = this->_data->window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                this->_data->window.close();
            }
            if(this->_data->input.isTextClicked(*this->_yes, sf::Mouse::Button::Left, this->_data->window)){
                this->_data->_delay.restart();
                this->_data->machine.RemoveState(3);
            }
            if(this->_data->input.isTextClicked(*this->_no, sf::Mouse::Button::Left, this->_data->window)){
                this->_data->_delay.restart();
                this->_data->machine.RemoveState(2);
            }
        }
    }

    void HomeState::Update(float dt){
        if(this->_data->input.hoverText(*this->_yes, this->_data->window)){
            this->_yes->setFillColor(sf::Color(0, 255, 255));
        }
        else this->_yes->setFillColor(sf::Color(225, 0, 255));

        if(this->_data->input.hoverText(*this->_no, this->_data->window)){
            this->_no->setFillColor(sf::Color(0, 255, 255));
        }
        else this->_no->setFillColor(sf::Color(225, 0, 255));
    }

    void HomeState::Draw(float dt){
        this->_data->window.clear();

        this->_data->window.draw(*this->_background);
        this->_data->window.draw(*this->_yes);
        this->_data->window.draw(*this->_no);
        this->_data->window.draw(*this->_quest);

        this->_data->window.display();
    }
}