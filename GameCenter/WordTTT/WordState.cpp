#include "WordState.h"


namespace Tokyo {

    WordState::WordState ( GameDataRef data, PlayerType playerType ) : _data( data ), _playerType( playerType ) {}

    void WordState::Init() {

        this->_WordBoard = std::make_shared<WordTTT_Board>();
        this->_player1 = std::make_shared<Player<char>>('X', PlayerType::HUMAN);
        this->_player2 = std::make_shared<Player<char>>('O', _playerType);
        this->_player1->set_board_ptr(_WordBoard.get());
        this->_player2->set_board_ptr(_WordBoard.get());
        this->_currentPlayer = _player1.get();

        this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND);
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("Grid", GRID);
        this->_data->assets.LoadTexture("cell", "../Assets/Textures/Cell.png");

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
        std::string A(1,'A');
        auto& let = this->_data->assets.GetTexture(A);
        
        this->_background = std::make_unique<sf::Sprite> ( background );
        this->_grid = std::make_unique<sf::Sprite> ( grid );
        this->_pauseButton = std::make_unique<sf::Sprite> ( pause );
        this->_letter = std::make_unique<sf::Sprite>( let );
        this->_currentCell = std::make_unique<sf::Sprite>( cell );

        this->_background->setPosition({SCREEN_WIDTH * 0.5f - background.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - background.getSize().y * 0.5f});
        this->_background->setColor( sf::Color( 255, 255, 255, 100 ) );

        this->_grid->setPosition({SCREEN_WIDTH * 0.5f - grid.getSize().x * 0.5f, SCREEN_HEIGHT * 0.5f - grid.getSize().y * 0.5f});

        this->_currentCell->setColor( sf::Color(135, 135, 135, 100) );

        this->_pauseButton->setPosition({pause.getSize().x * 0.3f, pause.getSize().y * 0.3f});
        this->_pauseButton->setColor( sf::Color( 255, 255, 255, 100 ) );

        this->_p1Score = std::make_unique<sf::Text>(font, "Player1: ", MAIN_MENU_TITLE_SIZE / 2.5);
        sf::FloatRect rect1 = _p1Score->getLocalBounds();
        this->_p1Score->setFillColor(sf::Color(240, 240, 220));
        this->_p1Score->setPosition({rect1.size.x * 0.3f, SCREEN_HEIGHT * 0.5f - rect1.size.y * 1.6f});

        this->_score1 = std::make_unique<sf::Text>(font, std::to_string(_WordBoard->get_p1_score()), MAIN_MENU_TITLE_SIZE / 2);
        this->_score1->setPosition({rect1.size.x * 0.7f, SCREEN_HEIGHT * 0.6f - rect1.size.y * 1.6f});
        this->_score1->setFillColor(sf::Color(240, 240, 220));

        this->_p2Score = std::make_unique<sf::Text>(font, "Player2: ", MAIN_MENU_TITLE_SIZE / 2.5);
        sf::FloatRect rect2 = _p2Score->getLocalBounds();
        this->_p2Score->setFillColor(sf::Color(240, 240, 220));
        this->_p2Score->setPosition({SCREEN_WIDTH - rect2.size.x * 1.3f, SCREEN_HEIGHT * 0.5f - rect2.size.y * 1.6f});

        this->_score2 = std::make_unique<sf::Text>(font, std::to_string(_WordBoard->get_p2_score()), MAIN_MENU_TITLE_SIZE / 2);
        this->_score2->setPosition({SCREEN_WIDTH - rect2.size.x * 0.9f, SCREEN_HEIGHT * 0.6f - rect2.size.y * 1.6f});
        this->_score2->setFillColor(sf::Color(240, 240, 220));

        auto gridSize = this->_grid->getTexture().getSize();
        this->gridPos = this->_grid->getPosition();
        this->CellWidth = gridSize.x / 3.0f;
        this->CellHeight = gridSize.y / 3.0f;
    }

    void WordState::HandleInput() {

        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }

            if(this->_data->input.isSpriteClicekd( *this->_grid, sf::Mouse::Button::Left, this->_data->window )){
                sf::Vector2i mousePos = this->_data->input.getMousePosition(this->_data->window);
                float localX = mousePos.x - gridPos.x;
                float localY = mousePos.y - gridPos.y;
                this->_row = localX / CellWidth;
                this->_col = localY / CellHeight;
                if (_WordBoard->get_cell(_row, _col) == ' '){
                    _cellChosen = true;
                }
            }

            if(_cellChosen){
                if (event->getIf<sf::Event::TextEntered>()){
                    char let = static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
                    char letter = std::toupper(let);
                    if(letter >= 'A' && letter <= 'Z'){
                        Move move(_row, _col, letter);
                        this->_WordBoard->update_board(&move);

                        if(_WordBoard->is_win(_currentPlayer)){
                            if(_currentPlayer = _player1.get()) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p1)), true);
                            else this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p2)), true);
                        }

                        else if(_WordBoard->is_draw(_currentPlayer)){
                            this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::draw)), true);
                        }

                        else if(_WordBoard->is_lose(_currentPlayer)){
                            if(_currentPlayer = _player1.get()) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p2)), true);
                            else this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p1)), true);
                        }

                        _cellChosen = false;
                        _currentPlayer = (_currentPlayer == _player1.get()) ? _player2.get() : _player1.get();  
                    }
                }
            }

            if(this->_data->input.isSpriteClicekd( *this->_pauseButton, sf::Mouse::Button::Left, this->_data->window )){
                this->_data->machine.AddState(StateRef (new PauseState(this->_data)), false);
            }
        }

        if (_playerType == PlayerType::COMPUTER && !_WordBoard->game_is_over(_currentPlayer) && _currentPlayer == _player2.get()){
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

            if(_WordBoard->is_win(_currentPlayer)){ 
                if(_currentPlayer = _player1.get()) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p1)), true);
                else this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p2)), true);
            }

            else if(_WordBoard->is_draw(_currentPlayer)){
                this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::draw)), true);
            }

            else if(_WordBoard->is_lose(_currentPlayer)){
                if(_currentPlayer = _player1.get()) this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p2)), true);
                else this->_data->machine.AddState(StateRef (new GameOverState(this->_data, GameID::Word, Winner::_p1)), true);
            }

            this->_currentPlayer = _player1.get();
        }
    }

    void WordState::Update( float dt ) {
        if (this->_data->input.hoverSprite( *this->_pauseButton, this->_data->window)){
            this->_pauseButton->setColor(sf::Color(255, 255, 255, 255));
        }
        else{
            this->_pauseButton->setColor(sf::Color(255, 255, 255, 100));
        }

        this->_score1->setString(std::to_string(_WordBoard->get_p1_score()));
        this->_score2->setString(std::to_string(_WordBoard->get_p2_score()));
    }

    void WordState::Draw( float dt ) {
        this->_data->window.clear();

        this->_data->window.draw( *this->_background);
        this->_data->window.draw( *this->_pauseButton);
        this->_data->window.draw( *this->_grid);
        
        if(_cellChosen){
            _currentCell->setPosition({(_row*4)+_row*CellWidth+gridPos.x, (_col*6)+_col*CellHeight+gridPos.y});
            this->_data->window.draw( *this->_currentCell );
        }
        
        for(int i=0; i<3; ++i){
            for (int j=0; j<3; ++j){
                if (this->_WordBoard->get_cell(i,j)!=' '){
                    std::string key (1,this->_WordBoard->get_cell(i,j));
                    auto letter = _data->assets.GetTexture(key);
                    _letter->setTexture(letter);
                    _letter->setPosition({(i*4)+i*CellWidth+gridPos.x, (j*6)+j*CellHeight+gridPos.y});
                    this->_data->window.draw( *this->_letter );
                }
            }
        }

        this->_data->window.draw( *this->_p1Score );
        this->_data->window.draw( *this->_p2Score );
        this->_data->window.draw( *this->_score1 );
        this->_data->window.draw( *this->_score2 );

        this->_data->window.display();
    }
}