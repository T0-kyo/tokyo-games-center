#include "GameOverState.h"
#include "ModeSelectionState.h"


namespace Tokyo {
    GameOverState::GameOverState(GameDataRef data, GameID gameID, Winner winner) : _data(data), _gameID(gameID), _winner(winner) {}

    void GameOverState::Init(){
        this->_data->assets.LoadTexture("Game Over bg", "../Assets/Textures/GameOver_Background.png");
        this->_data->assets.LoadTexture("Play Again", "../Assets/Textures/PlayAgain Button.png");
        this->_data->assets.LoadTexture("Go Home", "../Assets/Textures/Home Button.png");
        this->_data->assets.LoadTexture("Medal", "../Assets/Textures/Medal.png");

        auto& bg = _data->assets.GetTexture("Game Over bg");
        auto& play = _data->assets.GetTexture("Play Again");
        auto& home = _data->assets.GetTexture("Go Home");
        auto& medal = _data->assets.GetTexture("Medal");
        auto& font = _data->assets.GetFont("Main Font");

        this->_background = make_unique<sf::Sprite>( bg );
        this->_playAgain = make_unique<sf::Sprite>( play );
        this->_home = make_unique<sf::Sprite>( home );
        this->_medal = make_unique<sf::Sprite>( medal );

        if(_winner == Winner::p1) this->_announce = make_unique<sf::Text>( font, "Winner: Player1", MAIN_MENU_TITLE_SIZE / 1.5 );
        else if(_winner == Winner::p2) this->_announce = make_unique<sf::Text>( font, "Winner: Player2", MAIN_MENU_TITLE_SIZE / 1.5 );
        else if(_winner == Winner::draw) this->_announce = make_unique<sf::Text>( font, "Draw!", MAIN_MENU_TITLE_SIZE / 1.5 );
        sf::FloatRect rect = _announce->getGlobalBounds();

        this->_background->setPosition({SCREEN_WIDTH/2 - bg.getSize().x * 0.5f, SCREEN_HEIGHT/2 - bg.getSize().y * 0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 10));

        this->_playAgain->setPosition({SCREEN_WIDTH/2 + 300, SCREEN_HEIGHT/2 - play.getSize().y * 0.5f});
        this->_playAgain->setColor(sf::Color(255, 255, 255, 15));

        this->_home->setPosition({SCREEN_WIDTH/2 - 500, SCREEN_HEIGHT/2 - home.getSize().y * 0.5f});
        this->_home->setColor(sf::Color(255, 255, 255, 15));

        this->_medal->setPosition({SCREEN_WIDTH/2 + rect.size.x * 0.5f, rect.size.y * 0.5f});

        this->_announce->setPosition({SCREEN_WIDTH/2 - rect.size.x * 0.5f, rect.size.y * 0.7f});
        this->_announce->setFillColor(sf::Color(130, 51, 142));
    }

    void GameOverState::HandleInput(){
        while(auto event = this->_data->window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                this->_data->window.close();
            }
            if(_data->input.isSpriteClicked(*this->_home, sf::Mouse::Button::Left, this->_data->window)){
                this->_data->_delay.restart();
                this->_data->machine.RemoveState(1);
            }
            if(_data->input.isSpriteClicked(*this->_playAgain, sf::Mouse::Button::Left, _data->window)){
                this->_data->_delay.restart();
                switch(_gameID){
                    case GameID::Word://1
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::_4x4://2
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Infinity://3
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Sus://4
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::_5x5://5
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Misere://6
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Ultimate://7
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Pyramid://8
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::FourInARow://9
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Memory://10
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Obstacles://11
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Numerical://12
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    case GameID::Diamond://13
                        this->_data->machine.AddState( StateRef (new ModeSelectionState(_data, _gameID)), true);
                    default:
                        break;
                }
            }
        }
    }

    void GameOverState::Update( float dt ){
        if(_data->input.hoverSprite(*this->_home, this->_data->window)){
            this->_home->setColor(sf::Color(255, 255, 255, 250));
        }
        else this->_home->setColor(sf::Color(255, 255, 255, 15));

        if(_data->input.hoverSprite(*this->_playAgain, this->_data->window)){
            this->_playAgain->setColor(sf::Color(255, 255, 255, 250));
        }
        else this->_playAgain->setColor(sf::Color(255, 255, 255, 15));
        
    }

    void GameOverState::Draw( float dt ){

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_home );
        this->_data->window.draw( *this->_playAgain );
        if(_winner != Winner::draw) this->_data->window.draw( *this->_medal );
        this->_data->window.draw( *this->_announce );

        this->_data->window.display();
    }
}