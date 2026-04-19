#include "PauseState.h"
#include "HomeState.h"

namespace Tokyo{

    PauseState::PauseState( GameDataRef data, GameID gameId ) : _data( data ), _gameId( gameId ){}

    void PauseState::Init(){
        this->_data->assets.LoadTexture( "PauseBG", "../Assets/Textures/MainBackground.png" );
        this->_data->assets.LoadTexture( "Resume", "../Assets/Textures/Resume Button.png" );
        this->_data->assets.LoadTexture( "Home", "../Assets/Textures/Home Button.png" );
        this->_data->assets.LoadTexture( "Book", "../Assets/Textures/book.png" );

        this->_data->assets.LoadTexture( "rsus" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "r4x4" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "r5x5" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rdiamond" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rconnect4" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rinfinity" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rmemory" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rmisere" , "../Assets/Textures/misere-rules.png");
        this->_data->assets.LoadTexture( "rnumerical" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "robstacles" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rpyramid" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rultimate" , "../Assets/Textures/sus-rules.png");
        this->_data->assets.LoadTexture( "rword" , "../Assets/Textures/word-rules.png");

        switch(_gameId){
                    case GameID::Word://1
                        {auto& rulePage = this->_data->assets.GetTexture("rword");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::_4x4://2
                        {auto& rulePage = this->_data->assets.GetTexture("r4x4");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Infinity://3
                        {auto& rulePage = this->_data->assets.GetTexture("rinfinity");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Sus://4
                        {auto& rulePage = this->_data->assets.GetTexture("rsus");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::_5x5://5
                        {auto& rulePage = this->_data->assets.GetTexture("r5x5");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Misere://6
                        {auto& rulePage = this->_data->assets.GetTexture("rmisere");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Ultimate://7
                        {auto& rulePage = this->_data->assets.GetTexture("rultimate");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Pyramid://8
                        {auto& rulePage = this->_data->assets.GetTexture("rpyramid");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::FourInARow://9
                        {auto& rulePage = this->_data->assets.GetTexture("rconnect4");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Memory://10
                        {auto& rulePage = this->_data->assets.GetTexture("rmemory");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Obstacles://11
                        {auto& rulePage = this->_data->assets.GetTexture("robstacles");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Numerical://12
                        {auto& rulePage = this->_data->assets.GetTexture("rnumerical");
                        this->_rules = std::make_unique<sf::Sprite>( rulePage );
                        break;}
                    case GameID::Diamond://13
                        {auto& rulePage = this->_data->assets.GetTexture("rdiamond");
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