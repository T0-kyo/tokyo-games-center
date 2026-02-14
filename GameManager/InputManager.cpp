#include "InputManager.h"

using namespace std;

namespace Tokyo{

    bool InputManager::isSpriteClicekd ( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window ) {

        if ( sf::Mouse::isButtonPressed ( button )) {

            if (object.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {

            return true;
            }
        }
        return false;
    }

    bool InputManager::hoverSprite ( sf::Sprite object, sf::RenderWindow& window) {
        if ( object.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
            return true;
        }
        return false;
    }

    bool InputManager::isTextClicked ( sf::Text object, sf::Mouse::Button button, sf::RenderWindow& window ) {

        if ( sf::Mouse::isButtonPressed ( button )) {

            if (object.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {

            return true;
            }
        }
        return false;
    }

    bool InputManager::hoverText ( sf::Text object, sf::RenderWindow& window) {
        if ( object.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
            return true;
        }
        return false;
    }
    
    sf::Vector2i InputManager::getMousePosition( sf::RenderWindow& window ) {

    return sf::Mouse::getPosition(window);

    }
}