#include "NumericalState.h"


namespace Tokyo {

    NumericalState::NumericalState ( GameDataRef data, PlayerType playerType ) : _data( data ), _playerType( playerType ) {}

    void NumericalState::Init() {
        this->_NumericalBoard = std::make_shared<NumericalTTT_Board>();
        this->_Player1 = std::make_shared<Player<int>>(1, PlayerType::HUMAN);
        this->_Player2 = std::make_shared<Player<int>>(2, _playerType);
        this->_Player1->set_board_ptr(_NumericalBoard.get());
        this->_Player2->set_board_ptr(_NumericalBoard.get());
        this->_currentPlayer = _Player1.get();
        this->_p1_nums = _NumericalBoard->get_p1_nums();
        this->_p2_nums = _NumericalBoard->get_p2_nums();

        this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("Grid", GRID);
        this->_data->assets.LoadTexture("cell", CELL);

        for (int n=1; n<=9; ++n){
            std::string key = to_string(n);
            std::string path = "../Assets/Textures/" + key + ".png";
            this->_data->assets.LoadTexture( key, path );
        }

        auto& cell = this->_data->assets.GetTexture("cell");
        auto& grid = this->_data->assets.GetTexture("Grid");
        auto& pause = this->_data->assets.GetTexture("Pause Button");
        auto& background = this->_data->assets.GetTexture("Game Background");
        auto& font = this->_data->assets.GetFont("Main Font");
        auto& let = this->_data->assets.GetTexture("1");
        
        this->_background = std::make_unique<sf::Sprite> ( background );
        this->_grid = std::make_unique<sf::Sprite> ( grid );
        this->_pauseButton = std::make_unique<sf::Sprite> ( pause );
        this->_num = std::make_unique<sf::Sprite>( let );
        this->_currentCell = std::make_unique<sf::Sprite>( cell );

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

        _player1Nums = std::make_unique<sf::Text>(this->_data->assets.GetFont("Main Font"), std::to_string(_p1_nums[0]), MAIN_MENU_TITLE_SIZE/3);
        _player2Nums = std::make_unique<sf::Text>(this->_data->assets.GetFont("Main Font"), std::to_string(_p2_nums[0]), MAIN_MENU_TITLE_SIZE/3);

        auto gridSize = this->_grid->getTexture().getSize();
        this->gridPos = this->_grid->getPosition();
        this->CellWidth = gridSize.x / 3.0f;
        this->CellHeight = gridSize.y / 3.0f;
    }

    void NumericalState::HandleInput() {
        if(_gameOverClock.getElapsedTime().asSeconds() >= GAMEOVER_DELAY){
            if(_p1) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Numerical, Winner::p1)), true);
            else if(_p2) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Numerical, Winner::p2)), true);
            else if(_draw) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Numerical, Winner::draw)), true);
        }
        
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(_playerType != PlayerType::COMPUTER || _currentPlayer == _Player1.get()){
                if(this->_data->input.isSpriteClicked( *this->_grid, sf::Mouse::Button::Left, this->_data->window )){
                    sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                    float localX = mousePos.x - gridPos.x;
                    float localY = mousePos.y - gridPos.y;
                    this->_col = localX / CellWidth;
                    this->_row = localY / CellHeight;
                    if (_NumericalBoard->get_cell(_row, _col) == 0){
                        _cellChosen = true;
                    }
                    else _cellChosen = false;
                }

                if(_cellChosen){
                    if (event->getIf<sf::Event::TextEntered>()){
                        char num = static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
                        if(num >= '0' && num <= '9'){
                            Move move(_row, _col, num-'0');
                            if(this->_NumericalBoard->update_board(&move)){

                                _isUsed[num-'0'] = true;

                                if(_NumericalBoard->is_win(_currentPlayer)){
                                    if(_currentPlayer == _Player1.get()) _p1 = true;
                                    else _p2 = true;
                                }

                                else if(_NumericalBoard->is_draw(_currentPlayer)){
                                    _draw = true;
                                }

                                else if(_NumericalBoard->is_lose(_currentPlayer)){
                                    if(_currentPlayer == _Player1.get()) _p2 = true;
                                    else _p1 = true;
                                }

                                _cellChosen = false;
                                if(_playerType == PlayerType::HUMAN && !_NumericalBoard->game_is_over(_currentPlayer)) _currentPlayer = (_currentPlayer == _Player1.get()) ? _Player2.get() : _Player1.get();
                                else if(!_NumericalBoard->game_is_over(_currentPlayer)) _currentPlayer = _Player2.get();
                                _clock.restart();
                                _gameOverClock.restart();
                            }
                        }
                    }
                }
            }

            if(this->_data->input.isSpriteClicked( *this->_pauseButton, sf::Mouse::Button::Left, this->_data->window )){
                this->_data->machine.AddState(StateRef (new PauseState(this->_data)), false);
            }
        }
    }

    void NumericalState::Update ( float dt ) {
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

        if (_playerType == PlayerType::COMPUTER && !_NumericalBoard->game_is_over(_currentPlayer) && _currentPlayer == _Player2.get() && _clock.getElapsedTime().asSeconds() >= 1){
            int x, y;
            int num;
            do {
                x = rand() % 3;
                y = rand() % 3;
                num = _p2_nums[rand() %_p2_nums.size()];
            } while (this->_NumericalBoard->get_board_matrix()[x][y] != 0 || _isUsed[num]);

            Move move(x, y, num);
            this->_NumericalBoard->update_board(&move);

             _isUsed[num] = true;

            if(_NumericalBoard->is_win(_currentPlayer)){ 
                _p2 = true;
            }

            if(!_NumericalBoard->game_is_over(_currentPlayer)) this->_currentPlayer = _Player1.get();
        }
    }

    void NumericalState::Draw ( float dt ) {
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
                if (this->_NumericalBoard->get_cell(i,j)!=0){
                    std::string key = to_string(this->_NumericalBoard->get_cell(i,j));
                    auto letter = _data->assets.GetTexture(key);
                    _num->setTexture(letter);
                    _num->setPosition({(j*4)+j*CellWidth+gridPos.x, (i*6)+i*CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_num );
                }
            }
        }

        this->_data->window.draw( *this->_player1 );
        this->_data->window.draw( *this->_player2 );
        this->_data->window.draw( *this->_player1Turn );
        this->_data->window.draw( *this->_player2Turn );

        for(int i=0; i<_p1_nums.size(); ++i){
            _player1Nums->setString(std::to_string(_p1_nums[i]));
            _player1Nums->setPosition({100.0f + i*40, SCREEN_HEIGHT * 0.5f + 30});
            if(_isUsed[_p1_nums[i]]) _player1Nums->setFillColor(sf::Color(14, 73, 153, 0));
            else _player1Nums->setFillColor(sf::Color(14, 73, 153, 255));
            this->_data->window.draw( *this->_player1Nums );
        }

        for(int i=0; i<_p2_nums.size(); ++i){
            _player2Nums->setString(std::to_string(_p2_nums[i]));
            _player2Nums->setPosition({SCREEN_WIDTH - 285.0f + i*40, SCREEN_HEIGHT * 0.5f + 30});
            if(_isUsed[_p2_nums[i]]) _player2Nums->setFillColor(sf::Color(163, 11, 38, 0));
            else _player2Nums->setFillColor(sf::Color(163, 11, 38, 255));
            this->_data->window.draw( *this->_player2Nums );
        }

        this->_data->window.display();
    }
}