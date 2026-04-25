#pragma once

#include "../../DEFENITIONS.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Infinity_Board.h"
#include <cstdlib>
#include GAME_PLAY
#include GAME_PATH
#include STATE_PATH
#include GAMEOVER_STATE
#include PAUSE_STATE


namespace Tokyo {

    class InfinityState : public State {
    public:
        InfinityState(GameDataRef data , PlayerType playerType, bool isMute);

        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        private:
        GameDataRef _data;
        bool _isMute = false;

        std::unique_ptr<sf::Sound> _move;
        std::unique_ptr<sf::Sound> _option;
        std::unique_ptr<sf::Sound> _wrong;

        std::shared_ptr<Player<char>> _Player1;
        std::shared_ptr<Player<char>> _Player2;
        std::shared_ptr<Infinity_Board> _InfinityBoard;
        sf::Clock _clock;
        sf::Clock _gameOverClock;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _pauseButton;
        std::unique_ptr<sf::Sprite> _grid;
        std::unique_ptr<sf::Sprite> _x;
        std::unique_ptr<sf::Sprite> _o;
        std::unique_ptr<sf::Sprite> _Xwin;
        std::unique_ptr<sf::Sprite> _Owin;

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
    };
}