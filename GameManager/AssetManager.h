#pragma once

#include <map>

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"

using namespace std;


namespace Tokyo {

    // The AssetManager class is responsible for loading and managing all the textures and fonts used in the game.
    // It loads everything once at the start of the game then stores them in maps for easy access throughout the game. 
    // This way we can avoid loading the same texture or font multiple times and improve performance.
    class AssetManager {
        public:
        AssetManager() {}
        ~AssetManager() {}

        // Loads a texture from a file and stores it in the _textures map with the given name as the key.
        void LoadTexture( const string& name, const string& fileName );
        // Returns a reference to the texture stored in the _textures map with the given name as the key.
        sf::Texture& GetTexture( const string& name );

        // Loads a font from a file and stores it in the _fonts map with the given name as the key.
        void LoadFont( const string& name, const string& fileName );
        // Returns a reference to the font stored in the _fonts map with the given name as the key.
        sf::Font& GetFont( const string& name );

        // Loads a sound buffer from a file and stores it in the _soundBuffers map with the given name as the key.
        void LoadSound( const string& name, const string& fileName );
        // Returns a reference to the sound buffer stored in the _soundBuffers map with the given name as the key.
        sf::SoundBuffer& GetSound( const string& name );

        private:
        map<string, sf::Texture> _textures;   // Map that holds all the textures in the game, with the name of the texture as the key and the texture itself as the value.
        map<string, sf::Font> _fonts;    // Map that holds all the fonts in the game, with the name of the font as the key and the font itself as the value.
        map<string, sf::SoundBuffer> _soundBuffers;    // Map that holds all the sound buffers in the game, with the name of the sound as the key and the sound buffer itself as the value.
    };
}

