#include <SFML/Graphics.hpp>

#ifndef GAME_TILE_H
#define GAME_TILE_H

class GameTile {
public:
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
    GameTile(std::string texturePath,float x,float y);
    bool setUpSprite(std::string texturePath);
};

#endif

