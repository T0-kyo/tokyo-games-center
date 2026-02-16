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
        std::unique_ptr<sf::Text> _title;

        std::unique_ptr<sf::Text> _4x4TTT_Button;
        std::unique_ptr<sf::Text> _5x5TTT_Button;
        std::unique_ptr<sf::Text> _DiamondTTT_Button;
        std::unique_ptr<sf::Text> _FourInARow_Button;
        std::unique_ptr<sf::Text> _InfinityTTT_Button;
        std::unique_ptr<sf::Text> _MemoryTTT_Button;
        std::unique_ptr<sf::Text> _MisereTTT_Button;
        std::unique_ptr<sf::Text> _NumericalTTT_Button;
        std::unique_ptr<sf::Text> _ObstaclesTTT_Button;
        std::unique_ptr<sf::Text> _PyramidTTT_Button;
        std::unique_ptr<sf::Text> _SUS_Button;
        std::unique_ptr<sf::Text> _UltimateTTT_Button;
        std::unique_ptr<sf::Text> _WordTTT_Button;
    };
}