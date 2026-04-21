#pragma once

#include "../../DEFENITIONS.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Ultimate_Board.h"
#include <cstdlib>
#include GAME_PLAY
#include GAME_PATH
#include STATE_PATH
#include GAMEOVER_STATE
#include PAUSE_STATE


namespace Tokyo {

    class UltimateState : public State {
    public:
        UltimateState(GameDataRef data , PlayerType playerType);

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
        std::shared_ptr<Ultimate_Board> _UltimateBoard;
        sf::Clock _clock;
        sf::Clock _gameOverClock;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _pauseButton;
        std::unique_ptr<sf::Sprite> _grid;
        std::unique_ptr<sf::Sprite> _subgrid1;
        std::unique_ptr<sf::Sprite> _subgrid2;
        std::unique_ptr<sf::Sprite> _subgrid3;
        std::unique_ptr<sf::Sprite> _subgrid4;
        std::unique_ptr<sf::Sprite> _subgrid5;
        std::unique_ptr<sf::Sprite> _subgrid6;
        std::unique_ptr<sf::Sprite> _subgrid7;
        std::unique_ptr<sf::Sprite> _subgrid8;
        std::unique_ptr<sf::Sprite> _subgrid9;
        std::unique_ptr<sf::Sprite> _x;
        std::unique_ptr<sf::Sprite> _o;
        std::unique_ptr<sf::Sprite> _X;
        std::unique_ptr<sf::Sprite> _O;
        std::unique_ptr<sf::Sprite> _Xwin;
        std::unique_ptr<sf::Sprite> _Owin;

        std::unique_ptr<sf::Text> _player1;
        std::unique_ptr<sf::Text> _player2;
        std::unique_ptr<sf::Text> _player1Turn;
        std::unique_ptr<sf::Text> _player2Turn;

        bool _p1 = false;
        bool _p2 = false;
        bool _draw = false;

        bool _board1 = false;
        bool _board2 = false;
        bool _board3 = false;
        bool _board4 = false;
        bool _board5 = false;
        bool _board6 = false;
        bool _board7 = false;
        bool _board8 = false;
        bool _board9 = false;

        Player<char>* _currentPlayer;
        PlayerType _playerType;
        
        int _row;
        int _col;
        float CellWidth=0;
        float CellHeight=0;
        sf::Vector2f gridPos1;
        sf::Vector2f gridPos2;
        sf::Vector2f gridPos3;
        sf::Vector2f gridPos4;
        sf::Vector2f gridPos5;
        sf::Vector2f gridPos6;
        sf::Vector2f gridPos7;
        sf::Vector2f gridPos8;
        sf::Vector2f gridPos9;
    };
}