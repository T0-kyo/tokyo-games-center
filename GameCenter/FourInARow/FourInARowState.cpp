#include "FourInARowState.h"

namespace Tokyo {

    FourInARowState::FourInARowState ( GameDataRef data, PlayerType playerType, bool isMute ) : _data( data ), _playerType( playerType ), _isMute( isMute ) {}

    int FourInARowState::getLowestEmptyRow(int col) {
        for (int row = 5; row >= 0; --row) {   // scan bottom-up
            if (_fourinarowBoard->get_cell(row, col) == ' ')
                return row;
        }
        return -1;  // column full
        }

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
        this->_data->assets.LoadTexture("column", "../Assets/Textures/cell-c4.png");
        this->_data->assets.LoadTexture("blue", "../Assets/Textures/connect4-blue-icon.png");
        this->_data->assets.LoadTexture("red", "../Assets/Textures/connect4-red-icon.png");
        this->_data->assets.LoadSound("move", "../Assets/Audio/move-sound.wav");
        this->_data->assets.LoadSound("option", "../Assets/Audio/action-sound.wav");
        this->_data->assets.LoadSound("wrong", "../Assets/Audio/wrong-move.wav");

        auto& bg = this->_data->assets.GetTexture( "Background" );
        auto& pause = this->_data->assets.GetTexture( "Pause Button" );
        auto& grid = this->_data->assets.GetTexture( "Connect4 Grid" );
        auto& column = this->_data->assets.GetTexture( "column" );
        auto& blue = this->_data->assets.GetTexture( "blue" );
        auto& red = this->_data->assets.GetTexture( "red" );
        auto& font = this->_data->assets.GetFont("Main Font");
        auto& move = this->_data->assets.GetSound( "move" );
        auto& option = this->_data->assets.GetSound( "option" );
        auto& wrong = this->_data->assets.GetSound( "wrong" );

        this->_background = make_unique<sf::Sprite>( bg );
        this->_pauseButton = make_unique<sf::Sprite>( pause );
        this->_grid = make_unique<sf::Sprite>( grid );
        this->_currentColumn = make_unique<sf::Sprite>( column);
        this->_blue = make_unique<sf::Sprite>( blue );
        this->_red = make_unique<sf::Sprite>( red );
        this->_move = make_unique<sf::Sound>( move );
        this->_option = make_unique<sf::Sound>( option );
        this->_wrong = make_unique<sf::Sound>( wrong );

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
        this->CellWidth = gridSize.x / 7.0f;
        this->CellHeight = gridSize.y / 6.0f;
    }

    void FourInARowState::HandleInput() {
        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::FourInARow, Winner::p1, _isMute)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::FourInARow, Winner::p2, _isMute)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::FourInARow, Winner::draw, _isMute)), true);
        }

        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(!_p1 && !_p2 && !_draw){
                if(this->_data->input.isSpriteClicked(*this->_pauseButton, sf::Mouse::Button::Left, this->_data->window)){
                    if(!_isMute) this->_option->play();
                    this->_data->machine.AddState(StateRef (new PauseState(this->_data, GameID::FourInARow, _isMute)), false);
                }

                if(_playerType != PlayerType::COMPUTER || _currentPlayer == _Player1.get()){
                    if(this->_data->input.isSpriteClicked(*this->_grid, sf::Mouse::Button::Left, this->_data->window)){
                    sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                    float localX = mousePos.x - gridPos.x;
                    this->_col = static_cast<int>(localX / CellWidth);
                    this->_row = getLowestEmptyRow(this->_col);

                    if(this->_row != -1 && _clock.getElapsedTime().asMilliseconds() >= 150){
                        Move move(this->_row, this->_col, _currentPlayer->get_symbol());
                        this->_fourinarowBoard->update_board(&move);
                        if(!_isMute) this->_move->play();

                        if(_fourinarowBoard->is_win(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p1 = true;
                                else _p2 = true;
                        }
                        else if(_fourinarowBoard->is_draw(_currentPlayer)){
                            _draw = true;
                        }
                        if(_playerType == PlayerType::HUMAN && !_fourinarowBoard->game_is_over(_currentPlayer)) _currentPlayer = (_currentPlayer == _Player1.get()) ? _Player2.get() : _Player1.get();
                            else if(!_fourinarowBoard->game_is_over(_currentPlayer)) _currentPlayer = _Player2.get();
                            _clock.restart();
                            _gameOverClock.restart();
                    }
                    else if(this->_row == -1 && !_isMute) this->_wrong->play();
                    }
                }
            }
        }
    }

    void FourInARowState::Update ( float dt ) {
        if(this->_data->input.hoverSprite(*_pauseButton, _data->window)){
            _pauseButton->setColor(sf::Color(255, 255, 255, 255));
        }
        else _pauseButton->setColor(sf::Color(255, 255, 255, 180));

        if(this->_data->input.hoverSprite(*_grid, _data->window)){
            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
            float localX = mousePos.x - gridPos.x;
            int col = localX / CellWidth;
            this->_currentColumn->setPosition({gridPos.x + CellWidth * col, gridPos.y});
            this->_currentColumn->setColor(sf::Color(135, 135, 135, 100));
        }
        else this->_currentColumn->setColor(sf::Color(135, 135, 135, 0));

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

        if (_playerType == PlayerType::COMPUTER && !_fourinarowBoard->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1) {
            int col, row;
            do {
                col = rand() % 7;
                row = getLowestEmptyRow(col);
            } while (row == -1);
        
            Move move(row, col, _currentPlayer->get_symbol());
            this->_fourinarowBoard->update_board(&move);
            if(!_isMute) this->_move->play();
            
            if(_fourinarowBoard->is_win(_currentPlayer)){ 
                _p2 = true;
            }
            else if(_fourinarowBoard->is_draw(_currentPlayer)){
                _draw = true;
            }

            if(!_fourinarowBoard->game_is_over(_currentPlayer)) this->_currentPlayer = _Player1.get();

            _clock.restart();
            _gameOverClock.restart();
        }
    }

    void FourInARowState::Draw ( float dt ) {
        this->_data->window.clear( sf::Color::Black );

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_grid );
        this->_data->window.draw( *this->_currentColumn );
        this->_data->window.draw( *this->_pauseButton );
        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );

        for(int i = 0; i < 6; ++i){
            for(int j = 0; j < 7; ++j){
                if(this->_fourinarowBoard->get_cell(i,j) == 'X'){
                    this->_blue->setPosition({gridPos.x + j * CellWidth, gridPos.y + i * CellHeight});
                    this->_data->window.draw(*this->_blue);
                }
                else if(this->_fourinarowBoard->get_cell(i,j) == 'O'){
                    this->_red->setPosition({gridPos.x + j * CellWidth, gridPos.y + i * CellHeight});
                    this->_data->window.draw(*this->_red);
                }
            }
        }

        this->_data->window.display();
    }
}