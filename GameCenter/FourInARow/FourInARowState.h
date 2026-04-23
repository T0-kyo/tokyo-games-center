#pragma once

#include "../../DEFENITIONS.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "FourInARow_Board.h"
#include <cstdlib>
#include GAME_PLAY
#include GAME_PATH
#include STATE_PATH
#include GAMEOVER_STATE
#include PAUSE_STATE

namespace Tokyo {

    class FourInARowState : public State {
    public:
        FourInARowState(GameDataRef data , PlayerType playerType);

        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        private:
        GameDataRef _data;

        std::unique_ptr<sf::Sound> _move;
        std::unique_ptr<sf::Sound> _option;
        std::unique_ptr<sf::Sound> _wrong;

        std::shared_ptr<Player<char>> _Player1;
        std::shared_ptr<Player<char>> _Player2;
        std::shared_ptr<FourInARow_Board> _fourinarowBoard;
        sf::Clock _clock;
        sf::Clock _gameOverClock;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _pauseButton;
        std::unique_ptr<sf::Sprite> _grid;
        std::unique_ptr<sf::Sprite> _currentColumn;
        std::unique_ptr<sf::Sprite> _blue;
        std::unique_ptr<sf::Sprite> _red;

        std::unique_ptr<sf::Text> _player1;
        std::unique_ptr<sf::Text> _player2;
        std::unique_ptr<sf::Text> _player1Turn;
        std::unique_ptr<sf::Text> _player2Turn;

        bool _p1 = false;
        bool _p2 = false;
        bool _draw = false;

        Player<char>* _currentPlayer;
        PlayerType _playerType;

        int _row;
        int _col;
        float CellWidth=0;
        float CellHeight=0;
        sf::Vector2f gridPos;

        int getLowestEmptyRow(int col);
    };
}