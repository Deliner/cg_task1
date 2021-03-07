//
// Created by deliner on 06.03.2021.
//

#include "TextureManager.h"


TextureManager *TextureManager::manager = nullptr;


void TextureManager::init() {
    if (manager == nullptr) {
        manager = new TextureManager();
    }
}

sf::Texture *TextureManager::getTexture(TextureManager::Tiles type) {
    return manager->textures[type];
}

TextureManager::TextureManager() {
    for (auto & texture : textures) {
        texture = new sf::Texture();
    }

    textures[Tiles::WALL]->loadFromFile("images/wall.png");
    textures[Tiles::KEY]->loadFromFile("images/key.png");
    textures[Tiles::GRASS]->loadFromFile("images/grass.png");
    textures[Tiles::EMPTY]->loadFromFile("images/empty.png");
    textures[Tiles::DOOR]->loadFromFile("images/door.png");
    textures[Tiles::PLAYER]->loadFromFile("images/player.png");
}
