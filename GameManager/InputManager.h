#pragma once

#include <SFML/Graphics.hpp>


namespace Tokyo{

    class InputManager {
        public:
        InputManager() {};
        ~InputManager() {};

        // Checks if the sprite is clicked by passing the sprite I wanna check and the mouse click that was clicked and the window that  these events and these items are on.
        bool isSpriteClicekd ( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window );
        // Checks if the mouse is hovering over the sprite by passing the sprite I wanna check and the window that  these events and these items are on.
        bool hoverSprite ( sf::Sprite object, sf::RenderWindow& window );
        // Checks if the text is clicked by passing the text I wanna check and the mouse click that was clicked and the window that  these events and these items are on.
        bool isTextClicked ( sf::Text object, sf::Mouse::Button button, sf::RenderWindow& window );
        // Checks if the mouse is hovering over the text by passing the text I wanna check and the window that  these events and these items are on.
        bool hoverText ( sf::Text object, sf::RenderWindow& window );
        // Gets the mouse position on the window and returns it as a vector of integers
        sf::Vector2i getMousePosition( sf::RenderWindow& window );
    };
}