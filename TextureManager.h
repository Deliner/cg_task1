//
// Created by deliner on 06.03.2021.
//

#ifndef CG_TASK1_TEXTUREMANAGER_H
#define CG_TASK1_TEXTUREMANAGER_H

#include <vector>
#include "SFML/Graphics.hpp"

class TextureManager {

public:

    enum Tiles {
        WALL, KEY, GRASS, EMPTY, DOOR, PLAYER, DOOR_OPEN, COUNT
    };

    static void init();

    static sf::Texture *getTexture(Tiles);

private:
    TextureManager();

    sf::Texture *textures[COUNT];


private:
    static TextureManager *manager;
};


#endif //CG_TASK1_TEXTUREMANAGER_H
