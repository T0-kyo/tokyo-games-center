#include "WordState.h"


namespace Tokyo {

    WordState::WordState ( GameDataRef data, PlayerType playerType, bool isMute ) : _data( data ), _playerType( playerType ), _isMute( isMute ) {}

    void WordState::Init() {

        this->_WordBoard = std::make_shared<WordTTT_Board>();
        this->_Player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_Player1->set_board_ptr(_WordBoard.get());
        this->_Player2->set_board_ptr(_WordBoard.get());
        this->_currentPlayer = _Player1.get();

        this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("Grid", GRID);
        this->_data->assets.LoadTexture("cell", CELL);
        this->_data->assets.LoadSound("move", "../Assets/Audio/move-sound.wav");
        this->_data->assets.LoadSound("option", "../Assets/Audio/action-sound.wav");
        this->_data->assets.LoadSound("wrong", "../Assets/Audio/wrong-move.wav");

        for (char c='A'; c<='Z'; ++c){
            std::string key(1, c);
            std::string path = "../Assets/Textures/" + key + ".png";
            this->_data->assets.LoadTexture( key, path );
        }

        auto& cell = this->_data->assets.GetTexture("cell");
        auto& grid = this->_data->assets.GetTexture("Grid");
        auto& pause = this->_data->assets.GetTexture("Pause Button");
        auto& background = this->_data->assets.GetTexture("Game Background");
        auto& font = this->_data->assets.GetFont("Main Font");
        auto& let = this->_data->assets.GetTexture("A");
        auto& move = this->_data->assets.GetSound( "move" );
        auto& option = this->_data->assets.GetSound( "option" );
        auto& wrong = this->_data->assets.GetSound( "wrong" );
        
        this->_background = std::make_unique<sf::Sprite> ( background );
        this->_grid = std::make_unique<sf::Sprite> ( grid );
        this->_pauseButton = std::make_unique<sf::Sprite> ( pause );
        this->_letter = std::make_unique<sf::Sprite>( let );
        this->_currentCell = std::make_unique<sf::Sprite>( cell );
        this->_move = make_unique<sf::Sound>( move );
        this->_option = make_unique<sf::Sound>( option );
        this->_wrong = make_unique<sf::Sound>( wrong );

        this->_background->setPosition({SCREEN_WIDTH * 0.5f - background.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - background.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 100 ) );

        this->_grid->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});

        this->_currentCell->setColor( sf::Color(135, 135, 135, 100) );

        this->_pauseButton->setPosition({pause.getSize().x * 0.3f, pause.getSize().y * 0.3f});
        this->_pauseButton->setColor( sf::Color( 255, 255, 255, 100 ) );

        this->_player1 = std::make_unique<sf::Text>(font, "Player1: ", MAIN_MENU_TITLE_SIZE / 2.5);
        sf::FloatRect rect1 = _player1->getLocalBounds();
        this->_player1->setFillColor(sf::Color(14, 73, 153));
        this->_player1->setPosition({rect1.size.x * 0.3f, SCREEN_HEIGHT * 0.5f - rect1.size.y * 1.6f});

        this->_score1 = std::make_unique<sf::Text>(font, std::to_string(_WordBoard->get_p1_score()), MAIN_MENU_TITLE_SIZE / 2);
        this->_score1->setPosition({rect1.size.x * 0.7f, SCREEN_HEIGHT * 0.6f - rect1.size.y * 1.6f});
        this->_score1->setFillColor(sf::Color(240, 240, 220));

        this->_player2 = std::make_unique<sf::Text>(font, "Player2: ", MAIN_MENU_TITLE_SIZE / 2.5);
        sf::FloatRect rect2 = _player2->getLocalBounds();
        this->_player2->setFillColor(sf::Color(163, 11, 38));
        this->_player2->setPosition({SCREEN_WIDTH - rect2.size.x * 1.3f, SCREEN_HEIGHT * 0.5f - rect2.size.y * 1.6f});

        this->_score2 = std::make_unique<sf::Text>(font, std::to_string(_WordBoard->get_p2_score()), MAIN_MENU_TITLE_SIZE / 2);
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
        this->CellWidth = gridSize.x / 3.0f;
        this->CellHeight = gridSize.y / 3.0f;
    }

    void WordState::HandleInput() {
        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::p1, _isMute)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::p2, _isMute)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::draw, _isMute)), true);
        }
        
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(this->_data->input.isSpriteClicked( *this->_pauseButton, sf::Mouse::Button::Left, this->_data->window )){
                if(!_isMute) this->_option->play();
                this->_data->machine.AddState(StateRef (new PauseState(this->_data, GameID::Word, _isMute)), false);
            }

            if(_playerType != PlayerType::COMPUTER || _currentPlayer == _Player1.get()){
                if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window )){
                    sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                    float localX = mousePos.x - gridPos.x;
                    float localY = mousePos.y - gridPos.y;
                    this->_col = localX / CellWidth;
                    this->_row = localY / CellHeight;
                    if (_WordBoard->get_cell(_row, _col) == ' '){
                        _cellChosen = true;
                    }
                    else {
                        _cellChosen = false;
                        if (!_isMute) this->_wrong->play();
                    }
                }

                if(_cellChosen){
                    if (event->getIf<sf::Event::TextEntered>()){
                        char let = static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
                        char letter = std::toupper(let);
                        if(letter >= 'A' && letter <= 'Z'){
                            Move move(_row, _col, letter);
                            this->_WordBoard->update_board(&move);
                            if(!_isMute) this->_move->play();

                            if(_WordBoard->is_win(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p1 = true;
                                else _p2 = true;
                            }

                            else if(_WordBoard->is_draw(_currentPlayer)){
                                _draw = true;
                            }

                            else if(_WordBoard->is_lose(_currentPlayer)){
                                if(_currentPlayer == _Player1.get()) _p2 = true;
                                else _p1 = true;
                            }

                            _cellChosen = false;
                            if(_playerType == PlayerType::HUMAN && !_WordBoard->game_is_over(_currentPlayer)) _currentPlayer = (_currentPlayer == _Player1.get()) ? _Player2.get() : _Player1.get();
                            else if(!_WordBoard->game_is_over(_currentPlayer)) _currentPlayer = _Player2.get();
                            _clock.restart();
                            _gameOverClock.restart();
                        }
                        else if(!_isMute) this->_wrong->play();
                    }
                }
            }
        }
    }

    void WordState::Update( float dt ) {
        if (this->_data->input.hoverSprite( *this->_pauseButton, this->_data->window)){
            this->_pauseButton->setColor(sf::Color(255, 255, 255, 255));
        }
        else{
            this->_pauseButton->setColor(sf::Color(255, 255, 255, 180));
        }

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

        this->_score1->setString(std::to_string(_WordBoard->get_p1_score()));
        this->_score2->setString(std::to_string(_WordBoard->get_p2_score()));

        if (_playerType == PlayerType::COMPUTER && !_WordBoard->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1){
            int x, y;
            char sym;
            do {
                x = rand() % 3;
                y = rand() % 3;
                char letter = 'A' + (rand() % 26);
                sym = letter;
            } while (this->_WordBoard->get_board_matrix()[x][y] != ' ');

            Move move(x, y, sym);
        
            this->_WordBoard->update_board(&move);
            if(!_isMute) this->_move->play();

            if(_WordBoard->is_win(_currentPlayer)){ 
                if(_currentPlayer == _Player2.get()) _p2 = true;
                else _p1 = true;
            }

            else if(_WordBoard->is_draw(_currentPlayer)){
                _draw = true;
            }

            else if(_WordBoard->is_lose(_currentPlayer)){
                if(_currentPlayer == _Player1.get()) _p2 = true;
                else _p1 = true;
            }

            _currentPlayer = _Player1.get();
            _gameOverClock.restart();
        }
    }

    void WordState::Draw( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background);
        this->_data->window.draw( *this->_pauseButton);
        this->_data->window.draw( *this->_grid);
        
        if(_cellChosen){
            _currentCell->setPosition({(_col*5)+_col*CellWidth+gridPos.x, (_row*6)+_row*CellHeight+gridPos.y});
            this->_data->window.draw( *this->_currentCell );
        }
        
        for(int i=0; i<3; ++i){
            for (int j=0; j<3; ++j){
                if (this->_WordBoard->get_cell(i,j)!=' '){
                    std::string key (1,this->_WordBoard->get_cell(i,j));
                    auto letter = _data->assets.GetTexture(key);
                    _letter->setTexture(letter);
                    _letter->setPosition({(j*4)+j*CellWidth+gridPos.x, (i*6)+i*CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_letter );
                }
            }
        }

        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_score1 );
        this->_data->window.draw( *this->_score2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );

        this->_data->window.display();
    }
}