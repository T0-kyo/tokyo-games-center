#pragma once

#include "../../DEFENITIONS.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "WordTTT_Board.h"
#include GAME_PLAY
#include GAME_PATH
#include STATE_PATH
#include GAMEOVER_STATE
//#include PAUSE_STATE


namespace Tokyo {

    class WordState : public State {
    public:
        WordState(GameDataRef data , PlayerType playerType);

        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        private:
        GameDataRef _data;

        std::shared_ptr<Player<char>> _player1;
        std::shared_ptr<Player<char>> _player2;
        std::shared_ptr<WordTTT_Board> _WordBoard;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _letter;
        std::unique_ptr<sf::Sprite> _grid;
        std::unique_ptr<sf::Sprite> _pauseButton;
        std::unique_ptr<sf::Sprite> _currentCell;

        std::unique_ptr<sf::Text> _p1Score;
        std::unique_ptr<sf::Text> _p2Score;
        std::unique_ptr<sf::Text> _score1;
        std::unique_ptr<sf::Text> _score2;

        Player<char>* _currentPlayer;
        PlayerType _playerType;
        bool _cellChosen = false;
        int _row;
        int _col;
        float CellWidth=0;
        float CellHeight=0;
        sf::Vector2f gridPos;
    };
}