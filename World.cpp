//
// Created by deliner on 06.03.2021.
//

#include <fstream>
#include <string>
#include "World.h"
#include "TextureManager.h"

World::World(World::Callback *_callback) {
    callback = _callback;
    playerKeys = 0;
    loadLevels();
    setTiles();
}

void World::setTiles() {
    tiles = std::vector<std::vector<GameTile *>>(getLevelHeight());
    for (int i = 0; i < getLevelWidth(); i++) {
        auto vector = std::vector<GameTile *>(getLevelWidth());
        for (int j = 0; j < getLevelWidth(); j++) {
            vector[i] = new GameTile();
        }
        tiles[i] = vector;
    }
}

int World::getLevelWidth() {
    return 16;
}

int World::getLevelHeight() {
    return 9;
}

void World::makeMove(MoveDir dir) {
    if (currentLevel != nullptr) {
        currentLevel->makeMove(dir);
    }
}

void World::loadLevels() {
    std::ifstream mapFile("data/map");
    std::string line;
    std::getline(mapFile, line);
    int levelCount = std::stoi(line);
    levels = std::vector<Level *>(levelCount);
    for (int i = 0; i < levelCount; i++) {
        std::getline(mapFile, line);
        Level *level = getLevelFromLine(line);
        levels[level->id - 1] = level;
    }
    currentLevel = levels[0];
}

Level *World::getLevelFromLine(std::string line) {
    int id = '0' - line[0];
    int top = '0' - line[2];
    int right = '0' - line[3];
    int down = '0' - line[4];
    int left = '0' - line[5];
    return new Level(this, id, top, right, down, left, getMapFromFile(id));
}

std::vector<std::vector<char>> *World::getMapFromFile(int id) {
    auto *map = new std::vector<std::vector<char>>(getLevelHeight());
    std::ifstream mapFile("data/" + std::to_string(id));
    std::string line;
    for (int i = 0; i < getLevelHeight(); i++) {
        auto horizontal = std::vector<char>(getLevelWidth());
        std::getline(mapFile, line);
        for (int j = 0; j < getLevelWidth(); j++) {
            horizontal[j] = line[j];
        }
        (*map)[i] = horizontal;
    }
    return map;
}

int &World::getPlayerKeys() {
    return playerKeys;
}

void World::updateTiles() {
    auto map = currentLevel->map;
    for (int i = 0; i < getLevelHeight(); i++) {
        for (int j = 0; j < getLevelHeight(); j++) {
            tiles[i][j]->setData(std::pair<int, int>(i, j), charToTexture((*map)[i][j]));
        }
    }
    auto position = currentLevel->playerPos;
    tiles[position.first][position.second]->setData(position, TextureManager::getTexture(Tiles::PLAYER));
}

sf::Texture *World::charToTexture(char tile) {
    Tiles buf;
    if (tile == Level::WALL) {
        buf = Tiles::WALL;
    } else if (tile == Level::KEY) {
        buf = Tiles::KEY;
    } else if (tile == Level::GRASS) {
        buf = Tiles::GRASS;
    } else if (tile == Level::EMPTY) {
        buf = Tiles::EMPTY;
    } else if (tile == Level::DOOR) {
        buf = Tiles::DOOR;
    } else if (tile == Level::DOOR_OPEN) {
        buf = Tiles::DOOR_OPEN;
    } else if (tile == Level::PLAYER) {
        buf = Tiles::PLAYER;
    } else if (tile == Level::FINISH) {
        buf = Tiles::FINISH;
    } else {
        buf == Tiles::EMPTY;
    }
    return TextureManager::getTexture(buf);
}

void World::playerDied() {
    callback->onDeath();
}

void World::playerFinished() {
    callback->onFinish();
}

void World::loadLevel(int id) {
    levels[id]->setPlayerFromLevel(currentLevel->id - 1);
    currentLevel = levels[id - 1];
}
