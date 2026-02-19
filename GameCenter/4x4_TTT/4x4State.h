#pragma once

#include "../../DEFENITIONS.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "4x4_TTT_Board.h"
#include <cstdlib>
#include GAME_PLAY
#include GAME_PATH
#include STATE_PATH
#include GAMEOVER_STATE
#include PAUSE_STATE


namespace Tokyo {

    class State4x4 : public State {
    public:
        State4x4(GameDataRef data , PlayerType playerType);

        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        private:
        GameDataRef _data;

        std::shared_ptr<Player<char>> _player1;
        std::shared_ptr<Player<char>> _player2;
        std::shared_ptr<TTT4x4_Board> _4x4Board;
        sf::Clock _clock;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _x;
        std::unique_ptr<sf::Sprite> _o;
        std::unique_ptr<sf::Sprite> _xwin;
        std::unique_ptr<sf::Sprite> _owin;
        std::unique_ptr<sf::Sprite> _grid;
        std::unique_ptr<sf::Sprite> _pauseButton;
        std::unique_ptr<sf::Sprite> _currentCell;

        bool _p1 = false;
        bool _p2 = false;
        bool _draw = false;

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