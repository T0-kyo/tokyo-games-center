#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "State.h"
#include "../GameManager/Game.h"
#include <memory>
#include "../DEFENITIONS.h"


namespace Tokyo {
    class MainMenuState : public State {

        public:
        MainMenuState ( GameDataRef data );

        void Init();
        void HandleInput();
        void Update ( float dt );
        void Draw ( float dt );

        private:
        GameDataRef _data;

        std::unique_ptr<sf::Sprite> _background;
        std::unique_ptr<sf::Sprite> _logo;

        std::unique_ptr<sf::Sprite> _4x4TTT_Button;
        std::unique_ptr<sf::Sprite> _5x5TTT_Button;
        std::unique_ptr<sf::Sprite> _DiamondTTT_Button;
        std::unique_ptr<sf::Sprite> _FourInARow_Button;
        std::unique_ptr<sf::Sprite> _InfinityTTT_Button;
        std::unique_ptr<sf::Sprite> _MemoryTTT_Button;
        std::unique_ptr<sf::Sprite> _MisereTTT_Button;
        std::unique_ptr<sf::Sprite> _NumericalTTT_Button;
        std::unique_ptr<sf::Sprite> _ObstaclesTTT_Button;
        std::unique_ptr<sf::Sprite> _PyramidTTT_Button;
        std::unique_ptr<sf::Sprite> _SUS_Button;
        std::unique_ptr<sf::Sprite> _UltimateTTT_Button;
        std::unique_ptr<sf::Sprite> _WordTTT_Button;
    };
}