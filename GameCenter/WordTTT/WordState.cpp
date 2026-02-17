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


        for (char c='A'; c<='Z'; ++c){
            std::string key(1, c);
            std::string path = "../Assets/Textures/" + key + ".png";
            this->_data->assets.LoadTexture( key, path );
        }
    }

    void WordState::HandleInput() {
        while ( auto event = this->_data->window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                this->_data->window.close();
            }
        }
    }

    void WordState::Update( float dt ) {}

    void WordState::Draw( float dt ) {
        this->_data->window.clear( sf::Color::Black );
        this->_data->window.display();
    }
}