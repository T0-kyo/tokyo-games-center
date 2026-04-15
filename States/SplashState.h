#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "../GameManager/Game.h"
#include <memory>
#include "../DEFENITIONS.h"

namespace Tokyo {

    class SplashState : public State {

        public:
        SplashState( GameDataRef data );

        void Init();
        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

        private:
        GameDataRef _data;
        sf::Clock _clock;
        std::unique_ptr<sf::Sprite> _background;
        float _alpha = 0.f;

        enum class FadeState { FadeIn, Show, FadeOut };
        FadeState _phase = FadeState::FadeIn;
        float StartDelay = SPLASH_STATE_DELAY;
        float elapsed = 0.f;

        std::unique_ptr<sf::Sound> _intro;
    };
}