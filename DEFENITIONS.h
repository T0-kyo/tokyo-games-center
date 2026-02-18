#pragma once

#define SCREEN_WIDTH 1489 
#define SCREEN_HEIGHT 950

#define SPLASH_STATE_SHOW_TIME 3
#define FADE_EFFECT_DURATION 2.5f
#define SPLASH_STATE_DELAY 1.5f

#define MAIN_MENU_TITLE_SIZE 100

#define GAME_PLAY "../../GameManager/GamePlay.h"
#define STATE_PATH "../../States/State.h"
#define GAME_PATH "../../GameManager/Game.h"

#define PAUSE_STATE "../../States/PauseState"

#define SPLASH_BACKGROUND_FILEPATH "../Assets/Textures/Tokyo.jpg"

#define MAIN_MENU_BACKGROUND_FILEPATH "../Assets/Textures/MMBackground.jpg"
#define MAIN_MENU_TITLE_FILEPATH "../Assets/Fonts/Frijole-Regular.ttf"


enum class GameID {
    _4x4,
    _5x5,
    Diamond,
    FourInARow,
    Infinity,
    Memory,
    Misere,
    Numerical,
    Obstacles,
    Pyramid,
    Sus,
    Ultimate,
    Word,
};