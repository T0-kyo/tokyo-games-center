#pragma once

#include <SFML/Graphics.hpp>


namespace Tokyo{

    class InputManager {
        public:
        InputManager() {};
        ~InputManager() {};

        // Checks if the sprite is clicked by passing the sprite I wanna check and the mouse click that was clicked and the window that  these events and these items are on.
        bool isSpriteClicekd ( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window );  
        // Gets the mouse position on the window and returns it as a vector of integers
        sf::Vector2i getMousePosition( sf::RenderWindow& window );
    };
}