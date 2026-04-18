#include "FourInARowState.h"


namespace Tokyo {

    FourInARowState::FourInARowState ( GameDataRef data, PlayerType playerType ) : _data( data ) {}

    void FourInARowState::Init() {
        this->_fourinarowBoard = std::make_shared<FourInARow_Board>();
        this->_Player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_Player1->set_board_ptr(_fourinarowBoard.get());
        this->_Player2->set_board_ptr(_fourinarowBoard.get());
        this->_currentPlayer = _Player1.get();

        this->_data->assets.LoadTexture("Background", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("Connect4 Grid", "../Assets/Textures/connect4-grid.png");
        this->_data->assets.LoadTexture("x", "../Assets/Textures/_5X.png");
        this->_data->assets.LoadTexture("o", "../Assets/Textures/_5O.png");

        auto& bg = this->_data->assets.GetTexture( "Background" );
        auto& pause = this->_data->assets.GetTexture( "Pause Button" );
        auto& grid = this->_data->assets.GetTexture( "Connect4 Grid" );
        auto& X = this->_data->assets.GetTexture( "x" );
        auto& O = this->_data->assets.GetTexture( "o" );
        auto& font = this->_data->assets.GetFont("Main Font");

        this->_background = make_unique<sf::Sprite>( bg );
        this->_pauseButton = make_unique<sf::Sprite>( pause );
        this->_grid = make_unique<sf::Sprite>( grid );
        this->_x = make_unique<sf::Sprite>( X );
        this->_o = make_unique<sf::Sprite>( O );

        this->_background->setPosition({SCREEN_WIDTH/2 - bg.getSize().x * 0.5f, SCREEN_HEIGHT/2 - bg.getSize().y * 0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 100));

        this->_pauseButton->setPosition({pause.getSize().x * 0.3f, pause.getSize().y * 0.3f});
        this->_pauseButton->setColor( sf::Color( 255, 255, 255, 100 ) );

        this->_grid->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});

        this->_player1 = std::make_unique<sf::Text>(font, "Player1: ", MAIN_MENU_TITLE_SIZE / 2.5);
        sf::FloatRect rect1 = _player1->getLocalBounds();
        this->_player1->setFillColor(sf::Color(14, 73, 153));
        this->_player1->setPosition({rect1.size.x * 0.3f, SCREEN_HEIGHT * 0.5f - rect1.size.y * 1.6f});

        this->_player2 = std::make_unique<sf::Text>(font, "Player2: ", MAIN_MENU_TITLE_SIZE / 2.5);
        sf::FloatRect rect2 = _player2->getLocalBounds();
        this->_player2->setFillColor(sf::Color(163, 11, 38));
        this->_player2->setPosition({SCREEN_WIDTH - rect2.size.x * 1.3f, SCREEN_HEIGHT * 0.5f - rect2.size.y * 1.6f});

        this->_player1Turn = std::make_unique<sf::Text>(font, "Your Turn!", MAIN_MENU_TITLE_SIZE/4);
        this->_player1Turn->setFillColor(sf::Color(240, 240, 220));
        this->_player1Turn->setPosition({SCREEN_WIDTH * 0.06f, SCREEN_HEIGHT * 0.375f});

        this->_player2Turn = std::make_unique<sf::Text>(font, "Your Turn!", MAIN_MENU_TITLE_SIZE/4);
        this->_player2Turn->setFillColor(sf::Color(240, 240, 220, 0));
        this->_player2Turn->setPosition({SCREEN_WIDTH - SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.375f});

        auto gridSize = this->_grid->getTexture().getSize();
        this->gridPos = this->_grid->getPosition();
        this->CellWidth = gridSize.x / 5.0f;
        this->CellHeight = gridSize.y / 5.0f;
    }

    void FourInARowState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }
        
    void FourInARowState::Update ( float dt ) {
        if(this->_data->input.hoverSprite(*_pauseButton, _data->window)){
            _pauseButton->setColor(sf::Color(255, 255, 255, 255));
        }
        else _pauseButton->setColor(sf::Color(255, 255, 255, 180));

        if(_currentPlayer == _Player1.get()){
            _player1Turn->setFillColor(sf::Color(240, 240, 220, 255));
            _player2Turn->setFillColor(sf::Color(240, 240, 220, 0));
        }
        else if(_currentPlayer == _Player2.get()){
            _player2Turn->setFillColor(sf::Color(240, 240, 220, 255));
            _player1Turn->setFillColor(sf::Color(240, 240, 220, 0));
        }

        if(_p1 || _p2 || _draw){
            _player1Turn->setFillColor(sf::Color(240, 240, 220, 0));
            _player2Turn->setFillColor(sf::Color(240, 240, 220, 0));
        }
    }
        
    void FourInARowState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }

}