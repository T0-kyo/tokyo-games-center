#include "MemoryState.h"


namespace Tokyo {

    MemoryState::MemoryState ( GameDataRef data, PlayerType playerType, bool isMute ) : _data( data ), _playerType( playerType ), _isMute( isMute ) {}

    void MemoryState::Init() {
        this->_MemoryBoard = std::make_shared<MemoryTTT_Board>();
        this->_Player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_Player1->set_board_ptr(_MemoryBoard.get());
        this->_Player2->set_board_ptr(_MemoryBoard.get());
        this->_currentPlayer = _Player1.get();

        this->_data->assets.LoadTexture("Game bg", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("grid", GRID);
        this->_data->assets.LoadTexture("#", "../Assets/Textures/HASH.png");
        this->_data->assets.LoadTexture("X", "../Assets/Textures/_X.png");
        this->_data->assets.LoadTexture("O", "../Assets/Textures/_O.png");
        this->_data->assets.LoadTexture("X win", "../Assets/Textures/BLUE X.png");
        this->_data->assets.LoadTexture("O win", "../Assets/Textures/RED O.png");
        this->_data->assets.LoadSound("move", "../Assets/Audio/move-sound.wav");
        this->_data->assets.LoadSound("option", "../Assets/Audio/action-sound.wav");
        this->_data->assets.LoadSound("wrong", "../Assets/Audio/wrong-move.wav");

        auto& bg = this->_data->assets.GetTexture("Game bg");
        auto& pause = this->_data->assets.GetTexture("Pause Button");
        auto& grid = this->_data->assets.GetTexture("grid");
        auto& hash = this->_data->assets.GetTexture("#");
        auto& x = this->_data->assets.GetTexture("X");
        auto& o = this->_data->assets.GetTexture("O");
        auto& Xwin = this->_data->assets.GetTexture("X win");
        auto& Owin = this->_data->assets.GetTexture("O win");
        auto& font = this->_data->assets.GetFont("Main Font");
        auto& move = this->_data->assets.GetSound( "move" );
        auto& option = this->_data->assets.GetSound( "option" );
        auto& wrong = this->_data->assets.GetSound( "wrong" );

        this->_background = std::make_unique<sf::Sprite>(bg);
        this->_pauseButton= std::make_unique<sf::Sprite>(pause);
        this->_grid = std::make_unique<sf::Sprite>(grid);
        this->_hash = std::make_unique<sf::Sprite>(hash);
        this->_x = std::make_unique<sf::Sprite>(x);
        this->_o = make_unique<sf::Sprite>(o);
        this->_Xwin = std::make_unique<sf::Sprite>(Xwin);
        this->_Owin = std::make_unique<sf::Sprite>(Owin);
        this->_move = make_unique<sf::Sound>( move );
        this->_option = make_unique<sf::Sound>( option );
        this->_wrong = make_unique<sf::Sound>( wrong );

        this->_background->setPosition({SCREEN_WIDTH/2 - bg.getSize().x*0.5f, SCREEN_HEIGHT/2 - bg.getSize().y*0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 100));

        this->_pauseButton->setPosition({pause.getSize().x * 0.3f, pause.getSize().y * 0.3f});
        this->_pauseButton->setColor(sf::Color(255, 255, 255, 100));

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
        this->CellWidth = gridSize.x / 3.0f;
        this->CellHeight = gridSize.y / 3.0f;
    }

    void MemoryState::HandleInput() {

        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Memory, Winner::p1, _isMute)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Memory, Winner::p2, _isMute)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Memory, Winner::draw, _isMute)), true);
        }

        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(!_p1 && !_p2 && !_draw){
                if(this->_data->input.isSpriteClicked(*this->_pauseButton, sf::Mouse::Button::Left, this->_data->window)){
                    if(!_isMute) this->_option->play();
                    this->_data->machine.AddState(StateRef (new PauseState(this->_data, GameID::Memory, _isMute)), false);
                }

                if(_playerType != PlayerType::COMPUTER || _currentPlayer == _Player1.get()){
                    if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window )){
                        sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                        float localX = mousePos.x - gridPos.x;
                        float localY = mousePos.y - gridPos.y;
                        this->_col = localX / CellWidth;
                        this->_row = localY / CellHeight;
                        if (_MemoryBoard->get_cell(_row, _col) == ' ' && _clock.getElapsedTime().asMilliseconds() >= 150){
                            Move move(_row, _col, _currentPlayer->get_symbol());
                            this->_MemoryBoard->update_board(&move);
                            if(!_isMute) this->_move->play();

                            if(_MemoryBoard->is_win(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p1 = true;
                                else _p2 = true;
                            }
                            else if(_MemoryBoard->is_draw(_currentPlayer)){
                                _draw = true;
                            }

                            if(_playerType == PlayerType::HUMAN && !_MemoryBoard->game_is_over(_currentPlayer)) _currentPlayer = (_currentPlayer == _Player1.get()) ? _Player2.get() : _Player1.get();
                            else if(!_MemoryBoard->game_is_over(_currentPlayer)) _currentPlayer = _Player2.get();
                            _clock.restart();
                            _gameOverClock.restart();
                        }
                        else if(_MemoryBoard->get_cell(_row, _col) != ' ' && !_isMute && _clock.getElapsedTime().asMilliseconds() >= 150) this->_wrong->play();
                    }
                }
            }
        }
    }
        
    void MemoryState::Update ( float dt ) {
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

        if (_playerType == PlayerType::COMPUTER && !_MemoryBoard->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1){
            int x, y;
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (this->_MemoryBoard->get_board_matrix()[x][y] != ' ');

            Move move(x, y, _currentPlayer->get_symbol());
            this->_MemoryBoard->update_board(&move);
            if(!_isMute) this->_move->play();

            if(_MemoryBoard->is_win(_currentPlayer)){ 
                _p2 = true;
            }
            else if(_MemoryBoard->is_draw(_currentPlayer)){
                _draw = true;
            }

            if(!_MemoryBoard->game_is_over(_currentPlayer)) this->_currentPlayer = _Player1.get();
        }
    }
        
    void MemoryState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_pauseButton );
        this->_data->window.draw( *this->_grid );
        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );

        if(!_MemoryBoard->game_is_over(_currentPlayer)){
            for(int i=0; i<3; ++i){
                for(int j=0; j<3; ++j){
                    if(this->_MemoryBoard->get_cell(i,j)=='#'){
                        this->_hash->setPosition({(j*5)+j*CellWidth+gridPos.x, (i*3)+i*CellHeight+gridPos.y});
                        this->_data->window.draw( *this->_hash );
                    }
                }
            }
        }
        else {
            for(int i=0; i<3; ++i){
                for(int j=0; j<3; ++j){
                    if(this->_MemoryBoard->get_real_cell(i,j)=='O'){
                        this->_o->setPosition({(j*5)+j*CellWidth+gridPos.x, (i*3)+i*CellHeight+gridPos.y});
                        this->_data->window.draw( *this->_o );
                    }
                    else if(this->_MemoryBoard->get_real_cell(i,j)=='X'){
                        this->_x->setPosition({(j*5)+j*CellWidth+gridPos.x, (i*3)+i*CellHeight+gridPos.y});
                        this->_data->window.draw( *this->_x );
                    }
                }
            }

            for (int i = 0; i < _MemoryBoard->winner.size(); ++i){
                if(_p1){
                    this->_Xwin->setPosition({(_MemoryBoard->winner[i].second * 5) + _MemoryBoard->winner[i].second * CellWidth+gridPos.x, (_MemoryBoard->winner[i].first * 3) + _MemoryBoard->winner[i].first * CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_Xwin );
                }
                else if(_p2){
                    this->_Owin->setPosition({(_MemoryBoard->winner[i].second * 5) + _MemoryBoard->winner[i].second * CellWidth+gridPos.x, (_MemoryBoard->winner[i].first * 3) + _MemoryBoard->winner[i].first * CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_Owin );
                }
            }
        }

        this->_data->window.display();
    }

}