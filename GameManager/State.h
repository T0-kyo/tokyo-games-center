#pragma once

namespace Tokyo {

    // Abstract class for a state in the game. Each state (e.g. Main Menu, Gameplay, Pause Menu) 
    // will inherit from this class and implement its own version of the virtual functions.
    class state {
        public:
        virtual void Init() = 0;    //Initialize the state

        virtual void HandleInput() = 0;    //Handle user input
        virtual void Update( float dt ) = 0;    //Updates any variables or objects after receiving input
        virtual void Draw( float dt ) = 0;   //Draws the state to the screen with a delta time for smooth animations

        virtual void Pause() {};    //Pauses the current state, typically when another state is added on top of it (e.g. when the pause menu is opened during gameplay)
        virtual void Resume() {};   //Resumes the current state after being paused
    };
}