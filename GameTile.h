#include <SFML/Graphics.hpp>

#ifndef GAME_TILE_H
#define GAME_TILE_H

struct GameTile {
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;

    GameTile();

    GameTile(std::string texturePath, float x, float y);

    bool setUpSprite(std::string texturePath);

    void setData(std::pair<int, int> pos, sf::Texture *texture);
};

#endif

