#include "DiamondState.h"


namespace Tokyo {

    DiamondState::DiamondState ( GameDataRef data, PlayerType playerType ) : _data( data ), _playerType( playerType ) {}

    void DiamondState::Init() {
        this->_diamondBoard = std::make_shared<DiamondTTT_Board>();
        this->_Player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_Player1->set_board_ptr(_diamondBoard.get());
        this->_Player2->set_board_ptr(_diamondBoard.get());
        this->_currentPlayer = _Player1.get();

        this->_data->assets.LoadTexture("Game bg", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("grid", "../Assets/Textures/DiamondGrid.png");
        this->_data->assets.LoadTexture("X", "../Assets/Textures/diX.png");
        this->_data->assets.LoadTexture("O", "../Assets/Textures/diO.png");
        this->_data->assets.LoadTexture("X win", "../Assets/Textures/BLUE diX.png");
        this->_data->assets.LoadTexture("O win", "../Assets/Textures/RED diO.png");

        auto& bg = this->_data->assets.GetTexture("Game bg");
        auto& pause = this->_data->assets.GetTexture("Pause Button");
        auto& grid = this->_data->assets.GetTexture("grid");
        auto& x = this->_data->assets.GetTexture("X");
        auto& o = this->_data->assets.GetTexture("O");
        auto& Xwin = this->_data->assets.GetTexture("X win");
        auto& Owin = this->_data->assets.GetTexture("O win");
        auto& font = this->_data->assets.GetFont("Main Font");

        this->_background = std::make_unique<sf::Sprite>(bg);
        this->_pauseButton= std::make_unique<sf::Sprite>(pause);
        this->_grid = std::make_unique<sf::Sprite>(grid);
        this->_x = std::make_unique<sf::Sprite>(x);
        this->_o = make_unique<sf::Sprite>(o);
        this->_Xwin = std::make_unique<sf::Sprite>(Xwin);
        this->_Owin = std::make_unique<sf::Sprite>(Owin);

        this->_background->setPosition({SCREEN_WIDTH/2 - bg.getSize().x*0.5f, SCREEN_HEIGHT/2 - bg.getSize().y*0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 100));

        this->_pauseButton->setPosition({pause.getSize().x * 0.3f, pause.getSize().y * 0.3f});
        this->_pauseButton->setColor(sf::Color(255, 255, 255, 100));

        this->_grid->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.52f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});

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
        this->CellWidth = (gridSize.x - 70*2) / 7.0f;
        this->CellHeight = (gridSize.y - 65*2) / 7.0f;    
    }

    void DiamondState::HandleInput() {
        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Diamond, Winner::p1)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Diamond, Winner::p2)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Diamond, Winner::draw)), true);
        }

        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(!_p1 && !_p2 && !_draw){
                if(this->_data->input.isSpriteClicked(*this->_pauseButton, sf::Mouse::Button::Left, this->_data->window)){
                    this->_data->machine.AddState(StateRef (new PauseState(this->_data)), false);
                }

                if(_playerType != PlayerType::COMPUTER || _currentPlayer == _Player1.get()){
                    if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window )){
                        sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                        float localX = mousePos.x - gridPos.x;
                        float localY = mousePos.y - gridPos.y;
                        this->_col = (localX - 70)/ CellWidth;
                        this->_row = (localY - 65)/ CellHeight;
                        if (_row < 7 && _col < 7 && localX > 70 && localY > 65 && _diamondBoard->get_cell(_row, _col) == ' '){
                            Move move(_row, _col, _currentPlayer->get_symbol());
                            this->_diamondBoard->update_board(&move);

                            if(_diamondBoard->is_win(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p1 = true;
                                else _p2 = true;
                            }
                            else if(_diamondBoard->is_draw(_currentPlayer)){
                                _draw = true;
                            }

                            if(_playerType == PlayerType::HUMAN && !_diamondBoard->game_is_over(_currentPlayer)) _currentPlayer = (_currentPlayer == _Player1.get()) ? _Player2.get() : _Player1.get();
                            else if(!_diamondBoard->game_is_over(_currentPlayer)) _currentPlayer = _Player2.get();
                            _clock.restart();
                            _gameOverClock.restart();          
                        }
                    }
                }
            }
        }
    }

    void DiamondState::Update ( float dt ) {
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

        if (_playerType == PlayerType::COMPUTER && !_diamondBoard->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1){
            int x, y;
            do {
                x = rand() % 7;
                y = rand() % 7;
            } while (this->_diamondBoard->get_board_matrix()[x][y] != ' ');

            Move move(x, y, _currentPlayer->get_symbol());
            this->_diamondBoard->update_board(&move);

            if(_diamondBoard->is_win(_currentPlayer)){ 
                _p2 = true;
            }
            else if(_diamondBoard->is_draw(_currentPlayer)){
                _draw = true;
            }

            if(!_diamondBoard->game_is_over(_currentPlayer)) this->_currentPlayer = _Player1.get();
        }        
    }

    void DiamondState::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_pauseButton );
        this->_data->window.draw( *this->_grid );
        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );
        
        if(_p1){ 
            for(int i=0; i<7; ++i){
                for(int j=0; j<7; ++j){
                    if(this->_diamondBoard->get_cell(i,j)=='X'){
                        this->_Xwin->setPosition({j*CellWidth+gridPos.x + 81, i*CellHeight+gridPos.y + 77});
                        this->_data->window.draw( *this->_Xwin );
                    }
                    else if(this->_diamondBoard->get_cell(i,j)=='O'){
                        this->_o->setPosition({j*CellWidth+gridPos.x + 81, i*CellHeight+gridPos.y + 77});
                        this->_data->window.draw( *this->_o );
                    }
                }
            }
        }

        else if(_p2){
            for(int i=0; i<7; ++i){
                for(int j=0; j<7; ++j){
                    if(this->_diamondBoard->get_cell(i,j)=='O'){
                        this->_Owin->setPosition({j*CellWidth+gridPos.x + 81, i*CellHeight+gridPos.y + 77});
                        this->_data->window.draw( *this->_Owin );
                    }
                    else if(this->_diamondBoard->get_cell(i,j)=='X'){
                        this->_x->setPosition({j*CellWidth+gridPos.x + 81, i*CellHeight+gridPos.y + 77});
                        this->_data->window.draw( *this->_x );
                    }
                }
            }
        }

        else{
            for(int i=0; i<7; ++i){
                for(int j=0; j<7; ++j){
                    if(this->_diamondBoard->get_cell(i,j)=='O'){
                        this->_o->setPosition({j*CellWidth+gridPos.x + 81, i*CellHeight+gridPos.y + 77});
                        this->_data->window.draw( *this->_o );
                    }
                    else if(this->_diamondBoard->get_cell(i,j)=='X'){
                        this->_x->setPosition({j*CellWidth+gridPos.x + 81, i*CellHeight+gridPos.y + 77});
                        this->_data->window.draw( *this->_x );
                    }
                }
            }
        }        

        this->_data->window.display();
    }
}