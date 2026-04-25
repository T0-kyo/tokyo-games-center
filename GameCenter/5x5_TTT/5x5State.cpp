#include "5x5State.h"


namespace Tokyo {

    State5x5::State5x5 ( GameDataRef data, PlayerType playerType, bool isMute ) : _data( data ), _playerType( playerType ), _isMute( isMute ) {}

    void State5x5::Init() {
        this->_5x5Board = std::make_shared<TTT5x5_Board>();
        this->_Player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_Player1->set_board_ptr(_5x5Board.get());
        this->_Player2->set_board_ptr(_5x5Board.get());
        this->_currentPlayer = _Player1.get();

        this->_data->assets.LoadTexture("Background", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("5x5 Grid", "../Assets/Textures/Grid5x5.png");
        this->_data->assets.LoadTexture("x", "../Assets/Textures/_5X.png");
        this->_data->assets.LoadTexture("o", "../Assets/Textures/_5O.png");
        this->_data->assets.LoadTexture("x win", "../Assets/Textures/BLUE 5X.png");
        this->_data->assets.LoadTexture("o win", "../Assets/Textures/RED 5O.png");
        this->_data->assets.LoadSound("move", "../Assets/Audio/move-sound.wav");
        this->_data->assets.LoadSound("option", "../Assets/Audio/action-sound.wav");
        this->_data->assets.LoadSound("wrong", "../Assets/Audio/wrong-move.wav");

        auto& bg = this->_data->assets.GetTexture( "Background" );
        auto& pause = this->_data->assets.GetTexture( "Pause Button" );
        auto& grid = this->_data->assets.GetTexture( "5x5 Grid" );
        auto& X = this->_data->assets.GetTexture( "x" );
        auto& O = this->_data->assets.GetTexture( "o" );
        auto& Xwin = this->_data->assets.GetTexture( "x win" );
        auto& Owin = this->_data->assets.GetTexture( "o win" );
        auto& font = this->_data->assets.GetFont("Main Font");
        auto& move = this->_data->assets.GetSound( "move" );
        auto& option = this->_data->assets.GetSound( "option" );
        auto& wrong = this->_data->assets.GetSound( "wrong" );

        this->_background = make_unique<sf::Sprite>( bg );
        this->_pauseButton = make_unique<sf::Sprite>( pause );
        this->_grid = make_unique<sf::Sprite>( grid );
        this->_x = make_unique<sf::Sprite>( X );
        this->_o = make_unique<sf::Sprite>( O );
        this->_xWin = make_unique<sf::Sprite>( Xwin );
        this->_oWin = make_unique<sf::Sprite>( Owin );
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

        this->_score1 = std::make_unique<sf::Text>(font, std::to_string(this->_5x5Board->get_p1_score()), MAIN_MENU_TITLE_SIZE / 2);
        this->_score1->setPosition({rect1.size.x * 0.7f, SCREEN_HEIGHT * 0.6f - rect1.size.y * 1.6f});
        this->_score1->setFillColor(sf::Color(240, 240, 220));

        this->_player2 = std::make_unique<sf::Text>(font, "Player2: ", MAIN_MENU_TITLE_SIZE / 2.5);
        sf::FloatRect rect2 = _player2->getLocalBounds();
        this->_player2->setFillColor(sf::Color(163, 11, 38));
        this->_player2->setPosition({SCREEN_WIDTH - rect2.size.x * 1.3f, SCREEN_HEIGHT * 0.5f - rect2.size.y * 1.6f});

        this->_score2 = std::make_unique<sf::Text>(font, std::to_string(this->_5x5Board->get_p2_score()), MAIN_MENU_TITLE_SIZE / 2);
        this->_score2->setPosition({SCREEN_WIDTH - rect2.size.x * 0.9f, SCREEN_HEIGHT * 0.6f - rect2.size.y * 1.6f});
        this->_score2->setFillColor(sf::Color(240, 240, 220));

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

    void State5x5::HandleInput() {

        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::_5x5, Winner::p1)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::_5x5, Winner::p2)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::_5x5, Winner::draw)), true);
        }

        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(!_p1 && !_p2 && !_draw){
                if(this->_data->input.isSpriteClicked(*this->_pauseButton, sf::Mouse::Button::Left, this->_data->window)){
                    if(!_isMute) this->_option->play();
                    this->_data->machine.AddState(StateRef (new PauseState(this->_data, GameID::_5x5)), false);
                }

                if(_playerType != PlayerType::COMPUTER || _currentPlayer == _Player1.get()){
                    if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window )){
                        sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                        float localX = mousePos.x - gridPos.x;
                        float localY = mousePos.y - gridPos.y;
                        this->_col = localX / CellWidth;
                        this->_row = localY / CellHeight;
                        if (_5x5Board->get_cell(_row, _col) == ' '){
                            Move move(_row, _col, _currentPlayer->get_symbol());
                            this->_5x5Board->update_board(&move);
                            if(!_isMute) this->_move->play();

                            if(_5x5Board->is_win(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p1 = true;
                                else _p2 = true;
                            }
                            else if(_5x5Board->is_draw(_currentPlayer)){
                                _draw = true;
                            }

                            else if(_5x5Board->is_lose(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p2 = true;
                                else _p1 = true;
                            }

                            if(_playerType == PlayerType::HUMAN && !_5x5Board->game_is_over(_currentPlayer)) _currentPlayer = (_currentPlayer == _Player1.get()) ? _Player2.get() : _Player1.get();
                            else if(!_5x5Board->game_is_over(_currentPlayer)) _currentPlayer = _Player2.get();
                            _clock.restart();
                            _gameOverClock.restart();
                        }
                        else if(!_isMute) this->_wrong->play();
                    }
                }
            }
        }
    }
        
    void State5x5::Update ( float dt ) {
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

        this->_score1->setString(std::to_string(this->_5x5Board->get_p1_score()));
        this->_score2->setString(std::to_string(this->_5x5Board->get_p2_score()));

        if (_playerType == PlayerType::COMPUTER && !_5x5Board->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1){
            int x,y;
            do{
                x = rand() % 5;
                y = rand() % 5;
            } while(_5x5Board->get_cell(x, y) != ' ');

            Move move(x, y, 'O');
            this->_5x5Board->update_board(&move);
            if(!_isMute) this->_move->play();
            
            
            if(_5x5Board->is_win(_currentPlayer)){ 
                if(_currentPlayer == _Player2.get()) _p2 = true;
                else _p1 = true;
            }

            else if(_5x5Board->is_draw(_currentPlayer)){
                _draw = true;
            }

            else if(_5x5Board->is_lose(_currentPlayer)){
                if(_currentPlayer == _Player1.get()) _p2 = true;
                else _p1 = true;
            }

            if(!_5x5Board->game_is_over(_currentPlayer)) this->_currentPlayer = _Player1.get();

            _gameOverClock.restart();
        }

    }
        
    void State5x5::Draw ( float dt ) {
        this->_data->window.clear();
        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_grid );
        this->_data->window.draw( *this->_pauseButton );
        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_score1 );
        this->_data->window.draw( *this->_score2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );

        for(int i=0; i<5; ++i){
            for(int j=0; j<5; ++j){
                if(this->_5x5Board->get_cell(i,j)=='X'){
                    this->_x->setPosition({15+j*CellWidth+gridPos.x, 15+i*CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_x );
                }
                else if(this->_5x5Board->get_cell(i,j)=='O'){
                    this->_o->setPosition({15+j*CellWidth+gridPos.x, 15+i*CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_o );
                }
            }
        }

        if(_p1){
            for (int i = 0; i < _5x5Board->winnerX.size(); ++i){
                this->_xWin->setPosition({15 + _5x5Board->winnerX[i].second * CellWidth+gridPos.x, 15 + _5x5Board->winnerX[i].first * CellHeight+gridPos.y});
                this->_data->window.draw( *this->_xWin );
            }
        }
        else if(_p2){
            for (int i = 0; i < _5x5Board->winnerO.size(); ++i){
                this->_oWin->setPosition({15 + _5x5Board->winnerO[i].second * CellWidth+gridPos.x, 15 + _5x5Board->winnerO[i].first * CellHeight+gridPos.y});
                this->_data->window.draw( *this->_oWin );
            }
        }

        this->_data->window.display();
    }

}