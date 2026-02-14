#include "AssetManager.h"

namespace Tokyo {

    void AssetManager::LoadTexture( const string& name, const string& fileName ) {
        sf::Texture tex;

        if ( tex.loadFromFile( fileName )) {
            this->_textures[name] = tex;
        }
    }

    sf::Texture& AssetManager::GetTexture( const string& name ) {
        return this->_textures.at( name );
    }

    void AssetManager::LoadFont( const string& name, const string& fileName ) {
        sf::Font font;

        if ( font.openFromFile ( fileName )) {
            this->_fonts[name] = font;
        }
    }

    sf::Font& AssetManager::GetFont( const string& name ) {
        return this->_fonts.at( name );
    }

    void AssetManager::LoadSound( const string& name, const string& fileName ) {
        sf::SoundBuffer soundBuffer;

        if ( soundBuffer.loadFromFile( fileName )) {
            this->_soundBuffers[name] = soundBuffer;
        }
    }

    sf::SoundBuffer& AssetManager::GetSound( const string& name ) {
        return this->_soundBuffers.at( name );
    }


}

