#include "ModeSelectionState.h"
#include "../GameCenter/WordTTT/WordState.h"
#include "../GameCenter/UltimateTTT/UltimateState.h"
#include "../GameCenter/SUS/SUSState.h"
#include "../GameCenter/PyramidTTT/PyramidState.h"
#include "../GameCenter/ObstaclesTTT/ObstaclesState.h"
#include "../GameCenter/NumericalTTT/NumericalState.h"
#include "../GameCenter/MisereTTT/MisereState.h"
#include "../GameCenter/MemoryTTT/MemoryState.h"
#include "../GameCenter/InfinityTTT/InfinityState.h"
#include "../GameCenter/DiamondTTT/DiamondState.h"
#include "../GameCenter/FourInARow/FourInARowState.h"
#include "../GameCenter/4x4_TTT/4x4State.h"
#include "../GameCenter/5x5_TTT/5x5State.h"
#include "../GameManager/GamePlay.h"


namespace Tokyo {

    ModeSelectionState::ModeSelectionState ( GameDataRef data, GameID gameID ) : _data( data ), _gameID( gameID ) {}

    void ModeSelectionState::Init() {

        this->_data->assets.LoadTexture( "Mode Selection Background", MAIN_MENU_BACKGROUND_FILEPATH );
        this->_data->assets.LoadFont( "Mode Selection Choice", MAIN_MENU_TITLE_FILEPATH );

        auto& texture1 = this->_data->assets.GetTexture( "Mode Selection Background" );
        this->_background = std::make_unique<sf::Sprite> ( texture1 );

        auto& texture2 = this->_data->assets.GetFont( "Mode Selection Choice" );
        this->_choice1 = std::make_unique<sf::Text> ( texture2, "Player vs Player", MAIN_MENU_TITLE_SIZE/2 );
        sf::FloatRect textRect1 = this->_choice1->getLocalBounds();
        this->_choice2 = std::make_unique<sf::Text> ( texture2, "Player vs Computer", MAIN_MENU_TITLE_SIZE/2 );
        sf::FloatRect textRect2 = this->_choice2->getLocalBounds();

        this->_background->setPosition({SCREEN_WIDTH / 2 - texture1.getSize().x * 0.5f, SCREEN_HEIGHT / 2 - texture1.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 100 ) );
        this->_choice1->setPosition({SCREEN_WIDTH / 2 - textRect1.size.x * 0.5f, SCREEN_HEIGHT * 0.5f - textRect2.size.y * 1.3f});
        this->_choice1->setFillColor( sf::Color(225, 165, 35) );
        this->_choice2->setPosition({SCREEN_WIDTH / 2 - textRect2.size.x * 0.5f, SCREEN_HEIGHT * 0.5f + textRect2.size.y * 0.9f});
        this->_choice2->setFillColor( sf::Color(225, 165, 35) );
    }

    void ModeSelectionState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if ( this->_data->input.isTextClicked( *this->_choice1, sf::Mouse::Button::Left, this->_data->window ) ) {
                switch (this->_gameID) {
                    case GameID::Word:
                        this->_data->machine.AddState(StateRef(new WordState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Ultimate:
                        this->_data->machine.AddState(StateRef(new UltimateState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Sus:
                        this->_data->machine.AddState(StateRef(new SusState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Pyramid:
                        this->_data->machine.AddState(StateRef(new PyramidState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Obstacles:
                        this->_data->machine.AddState(StateRef(new ObstaclesState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Numerical:
                        this->_data->machine.AddState(StateRef(new NumericalState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Misere:
                        this->_data->machine.AddState(StateRef(new MisereState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Memory:
                        this->_data->machine.AddState(StateRef(new MemoryState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Infinity:
                        this->_data->machine.AddState(StateRef(new InfinityState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::Diamond:
                        this->_data->machine.AddState(StateRef(new DiamondState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::FourInARow:
                        this->_data->machine.AddState(StateRef(new FourInARowState(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::_4x4:
                        this->_data->machine.AddState(StateRef(new State4x4(this->_data, PlayerType::HUMAN)), true);
                        break;
                    case GameID::_5x5:
                        this->_data->machine.AddState(StateRef(new State5x5(this->_data, PlayerType::HUMAN)), true);
                        break;
                    default:
                        break;
                }
            }

            if ( this->_data->input.isTextClicked( *this->_choice2, sf::Mouse::Button::Left, this->_data->window ) ) {
                switch (this->_gameID) {
                    case GameID::Word:
                        this->_data->machine.AddState(StateRef(new WordState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Ultimate:
                        this->_data->machine.AddState(StateRef(new UltimateState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Sus:
                        this->_data->machine.AddState(StateRef(new SusState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Pyramid:
                        this->_data->machine.AddState(StateRef(new PyramidState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Obstacles:
                        this->_data->machine.AddState(StateRef(new ObstaclesState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Numerical:
                        this->_data->machine.AddState(StateRef(new NumericalState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Misere:
                        this->_data->machine.AddState(StateRef(new MisereState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Memory:
                        this->_data->machine.AddState(StateRef(new MemoryState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Infinity:
                        this->_data->machine.AddState(StateRef(new InfinityState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::Diamond:
                        this->_data->machine.AddState(StateRef(new DiamondState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::FourInARow:
                        this->_data->machine.AddState(StateRef(new FourInARowState(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::_4x4:
                        this->_data->machine.AddState(StateRef(new State4x4(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    case GameID::_5x5:
                        this->_data->machine.AddState(StateRef(new State5x5(this->_data, PlayerType::COMPUTER)), true);
                        break;
                    default:
                        break;
                }               
            }
        }
    }

    void ModeSelectionState::Update( float dt ) {

        if ( this->_data->input.hoverText( *this->_choice1, this->_data->window ) ) {
            this->_choice1->setFillColor( sf::Color(255, 255, 255) );
        } else {
            this->_choice1->setFillColor( sf::Color(225, 165, 35) );
        }

        if ( this->_data->input.hoverText( *this->_choice2, this->_data->window ) ) {
            this->_choice2->setFillColor( sf::Color(255, 255, 255) );
        } else {
            this->_choice2->setFillColor( sf::Color(225, 165, 35) );
        }
    }

    void ModeSelectionState::Draw( float dt ) {
        this->_data->window.clear();
        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_choice1 );
        this->_data->window.draw( *this->_choice2 );
        this->_data->window.display();
    }


}