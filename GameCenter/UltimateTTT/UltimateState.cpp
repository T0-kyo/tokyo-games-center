#include "UltimateState.h"


namespace Tokyo {

    UltimateState::UltimateState ( GameDataRef data , PlayerType playerType, bool isMute ) : _data( data ), _playerType( playerType ), _isMute( isMute ) {}

    void UltimateState::Init() {
        this->_UltimateBoard = std::make_shared<Ultimate_Board>();
        this->_Player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_Player1->set_board_ptr(_UltimateBoard.get());
        this->_Player2->set_board_ptr(_UltimateBoard.get());
        this->_currentPlayer = _Player1.get();

        this->_data->assets.LoadTexture("Game bg", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("grid", "../Assets/Textures/9x9 grid.png");
        this->_data->assets.LoadTexture("subgrid", "../Assets/Textures/subGrid.png");
        this->_data->assets.LoadTexture("x", "../Assets/Textures/_ult-x.png");
        this->_data->assets.LoadTexture("o", "../Assets/Textures/_ult-o.png");
        this->_data->assets.LoadTexture("X", "../Assets/Textures/_ultX.png");
        this->_data->assets.LoadTexture("O", "../Assets/Textures/_ultO.png");
        this->_data->assets.LoadTexture("X win", "../Assets/Textures/BLUE ultX.png");
        this->_data->assets.LoadTexture("O win", "../Assets/Textures/RED ultO.png");
        this->_data->assets.LoadSound("move", "../Assets/Audio/move-sound.wav");
        this->_data->assets.LoadSound("option", "../Assets/Audio/action-sound.wav");
        this->_data->assets.LoadSound("wrong", "../Assets/Audio/wrong-move.wav");

        auto& bg = this->_data->assets.GetTexture("Game bg");
        auto& pause = this->_data->assets.GetTexture("Pause Button");
        auto& grid = this->_data->assets.GetTexture("grid");
        auto& subgrid = this->_data->assets.GetTexture("subgrid");
        auto& x = this->_data->assets.GetTexture("x");
        auto& o = this->_data->assets.GetTexture("o");        
        auto& X = this->_data->assets.GetTexture("X");
        auto& O = this->_data->assets.GetTexture("O");
        auto& Xwin = this->_data->assets.GetTexture("X win");
        auto& Owin = this->_data->assets.GetTexture("O win");
        auto& font = this->_data->assets.GetFont("Main Font");
        auto& move = this->_data->assets.GetSound( "move" );
        auto& option = this->_data->assets.GetSound( "option" );
        auto& wrong = this->_data->assets.GetSound( "wrong" );

        this->_background = std::make_unique<sf::Sprite>(bg);
        this->_pauseButton= std::make_unique<sf::Sprite>(pause);
        this->_grid = std::make_unique<sf::Sprite>(grid);
        this->_subgrid1 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid2 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid3 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid4 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid5 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid6 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid7 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid8 = std::make_unique<sf::Sprite>(subgrid);
        this->_subgrid9 = std::make_unique<sf::Sprite>(subgrid);
        this->_x = std::make_unique<sf::Sprite>(x);
        this->_o = std::make_unique<sf::Sprite>(o);
        this->_X = std::make_unique<sf::Sprite>(X);
        this->_O = std::make_unique<sf::Sprite>(O);
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

        this->_subgrid1->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid2->setPosition({305 + SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid3->setPosition({612 + SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid4->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, 305 + SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid5->setPosition({305 + SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, 305 + SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid6->setPosition({612 + SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, 305 + SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid7->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, 612 + SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid8->setPosition({305 + SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, 612 + SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});
        this->_subgrid9->setPosition({612 + SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, 612 + SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});

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

        auto subgridSize = this->_subgrid1->getTexture().getSize();
        this->gridPos1 = this->_subgrid1->getPosition();
        this->gridPos2 = this->_subgrid2->getPosition();
        this->gridPos3 = this->_subgrid3->getPosition();
        this->gridPos4 = this->_subgrid4->getPosition();
        this->gridPos5 = this->_subgrid5->getPosition();
        this->gridPos6 = this->_subgrid6->getPosition();
        this->gridPos7 = this->_subgrid7->getPosition();
        this->gridPos8 = this->_subgrid8->getPosition();
        this->gridPos9 = this->_subgrid9->getPosition();
        this->CellWidth = subgridSize.x / 3.0f;
        this->CellHeight = subgridSize.y / 3.0f;
    }

    void UltimateState::HandleInput() {
        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Ultimate, Winner::p1, _isMute)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Ultimate, Winner::p2, _isMute)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Ultimate, Winner::draw, _isMute)), true);
        }
        
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(!_p1 && !_p2 && !_draw){ 
                if(this->_data->input.isSpriteClicked(*this->_pauseButton, sf::Mouse::Button::Left, this->_data->window)){
                    if(!_isMute) this->_option->play();
                    this->_data->machine.AddState(StateRef (new PauseState(this->_data, GameID::Ultimate, _isMute)), false);
                }

                if(_playerType != PlayerType::COMPUTER || _currentPlayer == _Player1.get()){
                    if(this->_data->input.isSpriteClicked( *this->_subgrid1, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid2, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid3, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid4, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid5, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid6, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid7, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid8, sf::Mouse::Button::Left, this->_data->window ) ||
                    this->_data->input.isSpriteClicked( *this->_subgrid9, sf::Mouse::Button::Left, this->_data->window )
                    ){  
                        if(this->_data->input.isSpriteClicked( *this->_subgrid1, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos1.x;
                            float localY = mousePos.y - gridPos1.y;
                            this->_col = localX / CellWidth;
                            this->_row = localY / CellHeight;
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid2, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos2.x;
                            float localY = mousePos.y - gridPos2.y;
                            this->_col = 3+(localX / CellWidth);
                            this->_row = localY / CellHeight;
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid3, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos3.x;
                            float localY = mousePos.y - gridPos3.y;
                            this->_col = 6+(localX / CellWidth);
                            this->_row = localY / CellHeight;
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid4, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos4.x;
                            float localY = mousePos.y - gridPos4.y;
                            this->_col = localX / CellWidth;
                            this->_row = 3+(localY / CellHeight);
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid5, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos5.x;
                            float localY = mousePos.y - gridPos5.y;
                            this->_col = 3+(localX / CellWidth);
                            this->_row = 3+(localY / CellHeight);
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid6, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos6.x;
                            float localY = mousePos.y - gridPos6.y;
                            this->_col = 6+(localX / CellWidth);
                            this->_row = 3+(localY / CellHeight);
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid7, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos7.x;
                            float localY = mousePos.y - gridPos7.y;
                            this->_col = localX / CellWidth;
                            this->_row = 6+(localY / CellHeight);
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid8, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos8.x;
                            float localY = mousePos.y - gridPos8.y;
                            this->_col = 3+(localX / CellWidth);
                            this->_row = 6+(localY / CellHeight);
                        }
                        if(this->_data->input.isSpriteClicked( *this->_subgrid9, sf::Mouse::Button::Left, this->_data->window )){
                            sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                            float localX = mousePos.x - gridPos9.x;
                            float localY = mousePos.y - gridPos9.y;
                            this->_col = 6+(localX / CellWidth);
                            this->_row = 6+(localY / CellHeight);
                        }
                    
                        if (_UltimateBoard->get_cell(_row, _col) == ' ' &&  _clock.getElapsedTime().asMilliseconds() >= 150){
                            Move move(_row, _col, _currentPlayer->get_symbol());
                            this->_UltimateBoard->update_board(&move);
                            if(!_isMute) this->_move->play();

                            if(_UltimateBoard->is_win(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p1 = true;
                                else _p2 = true;
                            }

                            if(_UltimateBoard->is_draw(_currentPlayer)){
                                _draw = true;
                            }

                            for(int i=0; i<3; ++i){
                                for(int j=0; j<3; ++j){
                                    if(this->_UltimateBoard->get_final_board_cell(i, j) != ' '){
                                        if(i==0 && j==0) _board1 = true;
                                        else if(i==0 && j==1) _board2 = true;
                                        else if(i==0 && j==2) _board3 = true;
                                        else if(i==1 && j==0) _board4 = true;
                                        else if(i==1 && j==1) _board5 = true;
                                        else if(i==1 && j==2) _board6 = true;
                                        else if(i==2 && j==0) _board7 = true;
                                        else if(i==2 && j==1) _board8 = true;
                                        else if(i==2 && j==2) _board9 = true;
                                    }
                                }
                            }

                            if(_playerType == PlayerType::HUMAN && !_UltimateBoard->game_is_over(_currentPlayer)) _currentPlayer = (_currentPlayer == _Player1.get()) ? _Player2.get() : _Player1.get();
                            else if(!_UltimateBoard->game_is_over(_currentPlayer)) _currentPlayer = _Player2.get();
                            _clock.restart();
                            _gameOverClock.restart();
                        }
                        else if(_UltimateBoard->get_cell(_row, _col) != ' ' && !_isMute &&  _clock.getElapsedTime().asMilliseconds() >= 150) this->_wrong->play();
                    }
                }
            }
        }
    }

    void UltimateState::Update ( float dt ) {
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

        if (_playerType == PlayerType::COMPUTER && !_UltimateBoard->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1){
            int x, y;
            do {
                x = rand() % 9;
                y = rand() % 9;
            } while (this->_UltimateBoard->get_board_matrix()[x][y] != ' ');

            Move move(x, y, _currentPlayer->get_symbol());
            this->_UltimateBoard->update_board(&move);
            if(!_isMute) this->_move->play();

            if(_UltimateBoard->is_win(_currentPlayer)){ 
                _p2 = true;
            }

            if(_UltimateBoard->is_draw(_currentPlayer)){
                _draw = true;
            }

            for(int i=0; i<3; ++i){
                for(int j=0; j<3; ++j){
                    if(this->_UltimateBoard->get_final_board_cell(i, j) != ' '){
                        if(i==0 && j==0) _board1 = true;
                        else if(i==0 && j==1) _board2 = true;
                        else if(i==0 && j==2) _board3 = true;
                        else if(i==1 && j==0) _board4 = true;
                        else if(i==1 && j==1) _board5 = true;
                        else if(i==1 && j==2) _board6 = true;
                        else if(i==2 && j==0) _board7 = true;
                        else if(i==2 && j==1) _board8 = true;
                        else if(i==2 && j==2) _board9 = true;
                    }
                }
            }

            if(!_UltimateBoard->game_is_over(_currentPlayer)) this->_currentPlayer = _Player1.get();

            _gameOverClock.restart();
        }
    }

    void UltimateState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_pauseButton );
        this->_data->window.draw( *this->_grid );
        this->_data->window.draw( *this->_subgrid1 );
        this->_data->window.draw( *this->_subgrid2 );
        this->_data->window.draw( *this->_subgrid3 );
        this->_data->window.draw( *this->_subgrid4 );
        this->_data->window.draw( *this->_subgrid5 );
        this->_data->window.draw( *this->_subgrid6 );
        this->_data->window.draw( *this->_subgrid7 );
        this->_data->window.draw( *this->_subgrid8 );
        this->_data->window.draw( *this->_subgrid9 );
        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );

        for (int k = 1; k <= 9; ++k) {
            for (int i = 0; i < 3; ++i) {
                for(int j = 0; j < 3; ++j){
                    switch(k){
                        case 1:
                            if(_board1){
                                if(_UltimateBoard->get_final_board_cell(0, 0) == 'X') {
                                    this->_X->setPosition({gridPos1.x, gridPos1.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(0, 0) == 'O') {
                                    this->_O->setPosition({gridPos1.x, gridPos1.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i, j) == 'X') {
                                    this->_x->setPosition({gridPos1.x + j*CellWidth + (j*3)+4, gridPos1.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i, j) == 'O') {
                                    this->_o->setPosition({gridPos1.x + j*CellWidth + (j*3)+4, gridPos1.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 2:
                            if(_board2){
                                if(_UltimateBoard->get_final_board_cell(0, 1) == 'X') {
                                    this->_X->setPosition({gridPos2.x, gridPos2.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(0, 1) == 'O') {
                                    this->_O->setPosition({gridPos2.x, gridPos2.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i, j+3) == 'X') {
                                    this->_x->setPosition({gridPos2.x + j*CellWidth + (j*3)+4, gridPos2.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i, j+3) == 'O') {
                                    this->_o->setPosition({gridPos2.x + j*CellWidth + (j*3)+4, gridPos2.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 3:
                            if(_board3){
                                if(_UltimateBoard->get_final_board_cell(0, 2) == 'X') {
                                    this->_X->setPosition({gridPos3.x, gridPos3.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(0, 2) == 'O') {
                                    this->_O->setPosition({gridPos3.x, gridPos3.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i, j+6) == 'X') {
                                    this->_x->setPosition({gridPos3.x + j*CellWidth + (j*3)+4, gridPos3.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i, j+6) == 'O') {
                                    this->_o->setPosition({gridPos3.x + j*CellWidth + (j*3)+4, gridPos3.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 4:
                            if(_board4){
                                if(_UltimateBoard->get_final_board_cell(1, 0) == 'X') {
                                    this->_X->setPosition({gridPos4.x, gridPos4.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(1, 0) == 'O') {
                                    this->_O->setPosition({gridPos4.x, gridPos4.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i+3, j) == 'X') {
                                    this->_x->setPosition({gridPos4.x + j*CellWidth + (j*3)+4, gridPos4.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i+3, j) == 'O') {
                                    this->_o->setPosition({gridPos4.x + j*CellWidth + (j*3)+4, gridPos4.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 5:
                            if(_board5){
                                if(_UltimateBoard->get_final_board_cell(1, 1) == 'X') {
                                    this->_X->setPosition({gridPos5.x, gridPos5.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(1, 1) == 'O') {
                                    this->_O->setPosition({gridPos5.x, gridPos5.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i+3, j+3) == 'X') {
                                    this->_x->setPosition({gridPos5.x + j*CellWidth + (j*3)+4, gridPos5.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i+3, j+3) == 'O') {
                                    this->_o->setPosition({gridPos5.x + j*CellWidth + (j*3)+4, gridPos5.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 6:
                            if(_board6){
                                if(_UltimateBoard->get_final_board_cell(1, 2) == 'X') {
                                    this->_X->setPosition({gridPos6.x, gridPos6.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(1, 2) == 'O') {
                                    this->_O->setPosition({gridPos6.x, gridPos6.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i+3, j+6) == 'X') {
                                    this->_x->setPosition({gridPos6.x + j*CellWidth + (j*3)+4, gridPos6.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i+3, j+6) == 'O') {
                                    this->_o->setPosition({gridPos6.x + j*CellWidth + (j*3)+4, gridPos6.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 7:
                            if(_board7){
                                if(_UltimateBoard->get_final_board_cell(2, 0) == 'X') {
                                    this->_X->setPosition({gridPos7.x, gridPos7.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(2, 0) == 'O') {
                                    this->_O->setPosition({gridPos7.x, gridPos7.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i+6, j) == 'X') {
                                    this->_x->setPosition({gridPos7.x + j*CellWidth + (j*3)+4, gridPos7.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i+6, j) == 'O') {
                                    this->_o->setPosition({gridPos7.x + j*CellWidth + (j*3)+4, gridPos7.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 8:
                            if(_board8){
                                if(_UltimateBoard->get_final_board_cell(2, 1) == 'X') {
                                    this->_X->setPosition({gridPos8.x, gridPos8.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(2, 1) == 'O') {
                                    this->_O->setPosition({gridPos8.x, gridPos8.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i+6, j+3) == 'X') {
                                    this->_x->setPosition({gridPos8.x + j*CellWidth + (j*3)+4, gridPos8.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i+6, j+3) == 'O') {
                                    this->_o->setPosition({gridPos8.x + j*CellWidth + (j*3)+4, gridPos8.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        case 9:
                            if(_board9){
                                if(_UltimateBoard->get_final_board_cell(2, 2) == 'X') {
                                    this->_X->setPosition({gridPos9.x, gridPos9.y}); 
                                    this->_data->window.draw( *this->_X );
                                }
                                else if(_UltimateBoard->get_final_board_cell(2, 2) == 'O') {
                                    this->_O->setPosition({gridPos9.x, gridPos9.y}); 
                                    this->_data->window.draw( *this->_O );
                                }
                            }
                            else {
                                if(_UltimateBoard->get_cell(i+6, j+6) == 'X') {
                                    this->_x->setPosition({gridPos9.x + j*CellWidth + (j*3)+4, gridPos9.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_x );
                                }
                                else if(_UltimateBoard->get_cell(i+6, j+6) == 'O') {
                                    this->_o->setPosition({gridPos9.x + j*CellWidth + (j*3)+4, gridPos9.y + i*CellHeight + (i*3)+4}); 
                                    this->_data->window.draw( *this->_o );
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        for (int i = 0; i < _UltimateBoard->winner.size(); ++i){
            if(_p1){
                if(_UltimateBoard->winner[i].first == 0 && _UltimateBoard->winner[i].second == 0){
                    this->_Xwin->setPosition({gridPos1.x, gridPos1.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 0 && _UltimateBoard->winner[i].second == 1){
                    this->_Xwin->setPosition({gridPos2.x, gridPos2.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 0 && _UltimateBoard->winner[i].second == 2){
                    this->_Xwin->setPosition({gridPos3.x, gridPos3.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 1 && _UltimateBoard->winner[i].second == 0){
                    this->_Xwin->setPosition({gridPos4.x, gridPos4.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 1 && _UltimateBoard->winner[i].second == 1){
                    this->_Xwin->setPosition({gridPos5.x, gridPos5.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 1 && _UltimateBoard->winner[i].second == 2){
                    this->_Xwin->setPosition({gridPos6.x, gridPos6.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 2 && _UltimateBoard->winner[i].second == 0){
                    this->_Xwin->setPosition({gridPos7.x, gridPos7.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 2 && _UltimateBoard->winner[i].second == 1){
                    this->_Xwin->setPosition({gridPos8.x, gridPos8.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
                if(_UltimateBoard->winner[i].first == 2 && _UltimateBoard->winner[i].second == 2){
                    this->_Xwin->setPosition({gridPos9.x, gridPos9.y}); 
                    this->_data->window.draw( *this->_Xwin );
                }
            }
            else if(_p2){
                if(_UltimateBoard->winner[i].first == 0 && _UltimateBoard->winner[i].second == 0){
                    this->_Owin->setPosition({gridPos1.x, gridPos1.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 0 && _UltimateBoard->winner[i].second == 1){
                    this->_Owin->setPosition({gridPos2.x, gridPos2.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 0 && _UltimateBoard->winner[i].second == 2){
                    this->_Owin->setPosition({gridPos3.x, gridPos3.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 1 && _UltimateBoard->winner[i].second == 0){
                    this->_Owin->setPosition({gridPos4.x, gridPos4.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 1 && _UltimateBoard->winner[i].second == 1){
                    this->_Owin->setPosition({gridPos5.x, gridPos5.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 1 && _UltimateBoard->winner[i].second == 2){
                    this->_Owin->setPosition({gridPos6.x, gridPos6.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 2 && _UltimateBoard->winner[i].second == 0){
                    this->_Owin->setPosition({gridPos7.x, gridPos7.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 2 && _UltimateBoard->winner[i].second == 1){
                    this->_Owin->setPosition({gridPos8.x, gridPos8.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
                if(_UltimateBoard->winner[i].first == 2 && _UltimateBoard->winner[i].second == 2){
                    this->_Owin->setPosition({gridPos9.x, gridPos9.y}); 
                    this->_data->window.draw( *this->_Owin );
                }
            }
        }

        this->_data->window.display();
    }
}