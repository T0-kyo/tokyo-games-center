#pragma once

#include "../../DEFENITIONS.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include GAME_PLAY
#include GAME_PATH
#include STATE_PATH


namespace Tokyo {

    class SusState : public State {
    public:
        SusState(GameDataRef data , PlayerType playerType);

        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

        private:
        GameDataRef _data;
    };
}