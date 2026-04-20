#include "PauseState.h"
#include "HomeState.h"

namespace Tokyo{

    PauseState::PauseState( GameDataRef data, GameID gameId ) : _data( data ), _gameId( gameId ){}

    void PauseState::Init(){
        this->_data->assets.LoadTexture( "PauseBG", "../Assets/Textures/MainBackground.png" );
        this->_data->assets.LoadTexture( "Resume", "../Assets/Textures/Resume Button.png" );
        this->_data->assets.LoadTexture( "Home", "../Assets/Textures/Home Button.png" );
        this->_data->assets.LoadTexture( "Book", "../Assets/Textures/book.png" );

        this->_data->assets.LoadTexture( "sus-rules" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "4x4-rules" , "../Assets/Textures/4x4-rules.png");
        this->_data->assets.LoadTexture( "5x5-rules" , "../Assets/Textures/5x5-rules.png");
        this->_data->assets.LoadTexture( "diamond-rules" , "../Assets/Textures/diamond-rules.png");
        this->_data->assets.LoadTexture( "connect4-rules" , "../Assets/Textures/connect4-rules.png");
        this->_data->assets.LoadTexture( "infinity-rules" , "../Assets/Textures/infinity-rules.png");
        this->_data->assets.LoadTexture( "memory-rules" , "../Assets/Textures/memory-rules.png");
        this->_data->assets.LoadTexture( "misere-rules" , "../Assets/Textures/misere-rules.png");
        this->_data->assets.LoadTexture( "numerical-rules" , "../Assets/Textures/numerical-rules.png");
        this->_data->assets.LoadTexture( "obstacles-rules" , "../Assets/Textures/obstacles-rules.png");
        this->_data->assets.LoadTexture( "pyramid-rules" , "../Assets/Textures/pyramid-rules.png");
        this->_data->assets.LoadTexture( "ultimate-rules" , "../Assets/Textures/ultimate-rules.png");
        this->_data->assets.LoadTexture( "word-rules" , "../Assets/Textures/word-rules.png");

        switch(_gameId){
                    case GameID::Word://1
                        {auto& rulePage = this->_data->assets.GetTexture("word-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::_4x4://2
                        {auto& rulePage = this->_data->assets.GetTexture("4x4-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Infinity://3
                        {auto& rulePage = this->_data->assets.GetTexture("infinity-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Sus://4
                        {auto& rulePage = this->_data->assets.GetTexture("sus-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::_5x5://5
                        {auto& rulePage = this->_data->assets.GetTexture("5x5-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Misere://6
                        {auto& rulePage = this->_data->assets.GetTexture("misere-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Ultimate://7
                        {auto& rulePage = this->_data->assets.GetTexture("ultimate-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Pyramid://8
                        {auto& rulePage = this->_data->assets.GetTexture("pyramid-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::FourInARow://9
                        {auto& rulePage = this->_data->assets.GetTexture("connect4-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Memory://10
                        {auto& rulePage = this->_data->assets.GetTexture("memory-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Obstacles://11
                        {auto& rulePage = this->_data->assets.GetTexture("obstacles-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Numerical://12
                        {auto& rulePage = this->_data->assets.GetTexture("numerical-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Diamond://13
                        {auto& rulePage = this->_data->assets.GetTexture("diamond-rules");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    default:
                        break;
                }

        auto& bg = this->_data->assets.GetTexture("PauseBG");
        auto& res = this->_data->assets.GetTexture("Resume");
        auto& hm = this->_data->assets.GetTexture("Home");
        auto& bk = this->_data->assets.GetTexture("Book");

        this->_background = std::make_unique<sf::Sprite>(bg);
        this->_resume = std::make_unique<sf::Sprite>(res);
        this->_home = std::make_unique<sf::Sprite>(hm);
        this->_book = std::make_unique<sf::Sprite>(bk);

        this->_background->setPosition({SCREEN_WIDTH / 2 - bg.getSize().x*0.5f, SCREEN_HEIGHT / 2 - bg.getSize().y*0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 70));

        this->_resume->setPosition({SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - res.getSize().y*0.5f});
        this->_resume->setColor(sf::Color(255, 255, 255, 150));

        this->_home->setPosition({SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - hm.getSize().y*0.5f});
        this->_home->setColor(sf::Color(255, 255, 255, 150));

        this->_book->setPosition({SCREEN_WIDTH * 0.03f, SCREEN_HEIGHT * 0.04f});
        this->_book->setColor(sf::Color(255, 255, 255, 150));

        this->_rules->setPosition({SCREEN_WIDTH / 2 - 357 , SCREEN_HEIGHT / 2 - 425});
        this->_rules->setColor(sf::Color(255, 255, 255, 0));
    }

    void PauseState::HandleInput(){
        while(auto event = this->_data->window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                this->_data->window.close();
            }
            if(!isRules){
                if(this->_data->input.isSpriteClicked(*this->_resume, sf::Mouse::Button::Left, this->_data->window)){
                    this->_data->_delay.restart();
                    this->_data->machine.RemoveState(1);
                }
                if(this->_data->input.isSpriteClicked(*this->_home, sf::Mouse::Button::Left, this->_data->window)){
                    this->_data->_delay.restart();
                    this->_data->machine.AddState(StateRef (new HomeState(this->_data)), false);
                }
            }
            if(this->_data->input.isSpriteClicked(*this->_book, sf::Mouse::Button::Left, this->_data->window)){
                isRules = 1 - isRules;
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

        if(isRules){
            this->_book->setColor(sf::Color(255, 255, 255, 255));
        }
        else this->_book->setColor(sf::Color(255, 255, 255, 150));

        if(isRules){
            this->_rules->setColor(sf::Color(255, 255, 255, 255));
        }
        else this->_rules->setColor(sf::Color(255, 255, 255, 0));
    }

    void PauseState::Draw(float dt){
        this->_data->window.clear();

        this->_data->window.draw(*this->_background);
        this->_data->window.draw(*this->_resume);
        this->_data->window.draw(*this->_home);
        this->_data->window.draw(*this->_book);
        this->_data->window.draw(*this->_rules);

        this->_data->window.display();
    }
}