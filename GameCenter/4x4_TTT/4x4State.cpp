#include "4x4State.h"

namespace Tokyo {

    State4x4::State4x4 ( GameDataRef data, PlayerType playerType, bool isMute ) : _data( data ), _playerType(playerType), _isMute( isMute ) {}

    void State4x4::Init() {

        this->_4x4Board = std::make_shared<TTT4x4_Board>();
        this->_Player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_Player1->set_board_ptr(_4x4Board.get());
        this->_Player2->set_board_ptr(_4x4Board.get());
        this->_currentPlayer = _Player1.get();

        this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("4x4 Grid", "../Assets/Textures/Grid4x4.png");
        this->_data->assets.LoadTexture("Cell", "../Assets/Textures/Cell4.png");
        this->_data->assets.LoadTexture("X sprite", "../Assets/Textures/_4X.png");
        this->_data->assets.LoadTexture("O sprite", "../Assets/Textures/_4O.png");
        this->_data->assets.LoadTexture("O win", "../Assets/Textures/RED 4O.png");
        this->_data->assets.LoadTexture("X win", "../Assets/Textures/BLUE 4X.png");
        this->_data->assets.LoadSound("move", "../Assets/Audio/move-sound.wav");
        this->_data->assets.LoadSound("option", "../Assets/Audio/action-sound.wav");
        this->_data->assets.LoadSound("wrong", "../Assets/Audio/wrong-move.wav");

        auto& bg = this->_data->assets.GetTexture( "Game Background" );
        auto& pause = this->_data->assets.GetTexture( "Pause Button" );
        auto& grid = this->_data->assets.GetTexture( "4x4 Grid" );
        auto& cell = this->_data->assets.GetTexture( "Cell" );
        auto& X = this->_data->assets.GetTexture( "X sprite" );
        auto& O = this->_data->assets.GetTexture( "O sprite" );
        auto& Xwin = this->_data->assets.GetTexture( "X win" );
        auto& Owin = this->_data->assets.GetTexture( "O win" );
        auto& font = this->_data->assets.GetFont( "Main Font" );
        auto& move = this->_data->assets.GetSound( "move" );
        auto& option = this->_data->assets.GetSound( "option" );
        auto& wrong = this->_data->assets.GetSound( "wrong" );

        this->_background = make_unique<sf::Sprite>( bg );
        this->_pauseButton = make_unique<sf::Sprite>( pause );
        this->_grid = make_unique<sf::Sprite>( grid );
        this->_currentCell = make_unique<sf::Sprite>( cell );
        this->_x = make_unique<sf::Sprite>( X );
        this->_o = make_unique<sf::Sprite>( O );
        this->_xwin = make_unique<sf::Sprite>( Xwin );
        this->_owin = make_unique<sf::Sprite>( Owin );
        this->_move = make_unique<sf::Sound>( move );
        this->_option = make_unique<sf::Sound>( option );
        this->_wrong = make_unique<sf::Sound>( wrong );

        this->_background->setPosition({SCREEN_WIDTH/2 - bg.getSize().x * 0.5f, SCREEN_HEIGHT/2 - bg.getSize().y * 0.5f});
        this->_background->setColor(sf::Color(255, 255, 255, 100));

        this->_pauseButton->setPosition({pause.getSize().x * 0.3f, pause.getSize().y * 0.3f});
        this->_pauseButton->setColor( sf::Color( 255, 255, 255, 100 ) );

        this->_grid->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});

        this->_currentCell->setColor( sf::Color(135, 135, 135, 100) );

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
        this->CellWidth = gridSize.x / 4.0f;
        this->CellHeight = gridSize.y / 4.0f;
    }

    void State4x4::HandleInput() {
        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::_4x4, Winner::p1, _isMute)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::_4x4, Winner::p2, _isMute)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::_4x4, Winner::draw, _isMute)), true);
        }
        
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(_data->input.isSpriteClicked(*_pauseButton, sf::Mouse::Button::Left, _data->window)){
                if(!_isMute) this->_option->play();
                this->_data->machine.AddState(StateRef (new PauseState(this->_data, GameID::_4x4, _isMute)), false);
            }

            if(_currentPlayer == _Player1.get()){
                if(_cellChosen){
                    if(event->getIf<sf::Event::KeyPressed>()){
                        auto arrow = event->getIf<sf::Event::KeyPressed>()->code;
                        char dir;
                        if(arrow == sf::Keyboard::Key::Up){
                            dir = 'U';
                        }
                        else if(arrow == sf::Keyboard::Key::Down){
                            dir = 'D';
                        }
                        else if(arrow == sf::Keyboard::Key::Left){
                            dir = 'L';
                        }
                        else if(arrow == sf::Keyboard::Key::Right){
                            dir = 'R';
                        }
                        
                        if(dir=='U' || dir=='D' || dir=='L' || dir=='R'){
                            Move move(_row, _col, dir);
                            if(this->_4x4Board->update_board(&move)){
                                if(!_isMute) this->_move->play();

                                if(_4x4Board->is_win(_currentPlayer)) _p1 = true;

                                else if(_4x4Board->is_draw(_currentPlayer)) _draw = true;

                                _cellChosen = false;
                                _currentPlayer = _Player2.get();
                                _clock.restart();
                                _gameOverClock.restart();
                            }
                            else if(!_isMute) this->_wrong->play();
                        }
                    }
                    if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window)){
                        sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                        float localX = mousePos.x - gridPos.x;
                        float localY = mousePos.y - gridPos.y;
                        int col = localX / CellWidth;
                        int row = localY / CellHeight;
                        char dir;

                        if(col==_col && row==_row-1){
                            dir = 'U';
                        }
                        else if(col==_col && row==_row+1){
                            dir = 'D';
                        }
                        else if(col==_col+1 && row==_row){
                            dir = 'R';
                        }
                        else if(col==_col-1 && row==_row){
                            dir = 'L';
                        }
                        else _cellChosen = false;

                        if(dir=='U' || dir=='D' || dir=='L' || dir=='R'){
                            Move move(_row, _col, dir);
                            if(this->_4x4Board->update_board(&move)){
                                if(!_isMute) this->_move->play();

                                if(_4x4Board->is_win(_currentPlayer)) _p1 = true;

                                else if(_4x4Board->is_draw(_currentPlayer)) _draw = true;

                                _currentPlayer = _Player2.get();
                                _clock.restart();
                                _gameOverClock.restart();
                            }
                            else if(!_isMute) this->_wrong->play();
                            _cellChosen = false;
                        }
                    }
                }

                if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window)){
                    sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                    float localX = mousePos.x - gridPos.x;
                    float localY = mousePos.y - gridPos.y;
                    this->_col = localX / CellWidth;
                    this->_row = localY / CellHeight;
                    if (!_cellChosen && _4x4Board->get_cell(_row, _col) == 'X' && _currentPlayer == _Player1.get()){
                        _cellChosen = true;
                    }
                }
            }

            else if(_currentPlayer == _Player2.get() && _playerType == PlayerType::HUMAN){
                if(_cellChosen){
                    if(event->getIf<sf::Event::KeyPressed>()){
                        auto arrow = event->getIf<sf::Event::KeyPressed>()->code;
                        char dir;
                        if(arrow == sf::Keyboard::Key::Up){
                            dir = 'U';
                        }
                        else if(arrow == sf::Keyboard::Key::Down){
                            dir = 'D';
                        }
                        else if(arrow == sf::Keyboard::Key::Left){
                            dir = 'L';
                        }
                        else if(arrow == sf::Keyboard::Key::Right){
                            dir = 'R';
                        }
                        
                        if(dir=='U' || dir=='D' || dir=='L' || dir=='R'){
                            Move move(_row, _col, dir);
                            if(this->_4x4Board->update_board(&move)){
                                if(!_isMute) this->_move->play();

                                if(_4x4Board->is_win(_currentPlayer)) _p2 = true;

                                else if(_4x4Board->is_draw(_currentPlayer)) _draw = true;

                                _cellChosen = false;
                                _currentPlayer = _Player1.get();
                                _wait.restart();
                                _gameOverClock.restart();
                            }
                            else if(!_isMute) this->_wrong->play();
                        }
                    }

                    else if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window)){
                        sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                        float localX = mousePos.x - gridPos.x;
                        float localY = mousePos.y - gridPos.y;
                        int col = localX / CellWidth;
                        int row = localY / CellHeight;
                        char dir;

                        if(col==_col && row==_row-1){
                            dir = 'U';
                        }
                        else if(col==_col && row==_row+1){
                            dir = 'D';
                        }
                        else if(col==_col+1 && row==_row){
                            dir = 'R';
                        }
                        else if(col==_col-1 && row==_row){
                            dir = 'L';
                        }
                        else _cellChosen = false;

                        if(dir=='U' || dir=='D' || dir=='L' || dir=='R'){
                            Move move(_row, _col, dir);
                            if(this->_4x4Board->update_board(&move)){
                                if(!_isMute) this->_move->play();

                                if(_4x4Board->is_win(_currentPlayer)) _p2 = true;

                                else if(_4x4Board->is_draw(_currentPlayer)) _draw = true;

                                _currentPlayer = _Player1.get();
                                _wait.restart();
                                _gameOverClock.restart();
                            }
                            else if(!_isMute) this->_wrong->play();
                            _cellChosen = false;
                        }
                    }
                }
                
                if(this->_wait.getElapsedTime().asSeconds() > 0.12f && this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window )){
                    sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                    float localX = mousePos.x - gridPos.x;
                    float localY = mousePos.y - gridPos.y;
                    this->_col = localX / CellWidth;
                    this->_row = localY / CellHeight;
                    if (!_cellChosen && _4x4Board->get_cell(_row, _col) == 'O'){
                        _cellChosen = true;
                    }
                }
            }
            
        }
    }
        
    void State4x4::Update ( float dt ) {
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

        if (_playerType == PlayerType::COMPUTER && !_4x4Board->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1){
            int x, y;
            char sym;
            do {
                x = rand() % 4;
                y = rand() % 4;
                int a = rand() % 4;
                char arrow[4]={'U', 'D', 'L', 'R'};
                sym = arrow[a];
            } while (this->_4x4Board->get_board_matrix()[x][y] != 'O');

            Move move(x, y, sym);
        
            if(this->_4x4Board->update_board(&move)){
                if(!_isMute) this->_move->play();

                if(_4x4Board->is_win(_currentPlayer)){ 
                    _p2 = true;
                }

                else if(_4x4Board->is_draw(_currentPlayer)){
                    _draw = true;
                }

                this->_currentPlayer = _Player1.get();

                _gameOverClock.restart();
            }
        }
    }
        
    void State4x4::Draw ( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background );
        this->_data->window.draw( *this->_grid );
        this->_data->window.draw( *this->_pauseButton );
        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );

        if(_cellChosen){
            this->_currentCell->setPosition({_col*CellWidth+gridPos.x+(_col*3), _row*CellHeight+gridPos.y+(_row*3)});
            this->_data->window.draw( *this->_currentCell );
        }

        for(int i=0; i<4; ++i){
            for(int j=0; j<4; ++j){
                if(this->_4x4Board->get_cell(i,j)=='X'){
                    this->_x->setPosition({(j*3)+j*CellWidth+gridPos.x, (i*3)+i*CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_x );
                }
                else if(this->_4x4Board->get_cell(i,j)=='O'){
                    this->_o->setPosition({(j*3)+j*CellWidth+gridPos.x, (i*3)+i*CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_o );
                }
            }
        }

        if(_p1){
            for (int i = 0; i < _4x4Board->winner.size(); ++i){
                this->_xwin->setPosition({(_4x4Board->winner[i].second * 3) + _4x4Board->winner[i].second * CellWidth+gridPos.x, (_4x4Board->winner[i].first * 3) + _4x4Board->winner[i].first * CellHeight+gridPos.y});
                this->_data->window.draw( *this->_xwin );
            }
        }
        if(_p2){
            for (int i = 0; i < _4x4Board->winner.size(); ++i){
                this->_owin->setPosition({(_4x4Board->winner[i].second * 3) + _4x4Board->winner[i].second * CellWidth+gridPos.x, (_4x4Board->winner[i].first * 3) + _4x4Board->winner[i].first * CellHeight+gridPos.y});
                this->_data->window.draw( *this->_owin );
            }
        }

        this->_data->window.display();
    }

}