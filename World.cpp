//
// Created by deliner on 06.03.2021.
//

#include <fstream>
#include <string>
#include "World.h"

World::World(Callback *_callback) {
    callback = _callback;
    playerKeys = 0;
    loadLevels();

}

int World::getLevelWidth() {
    return 16;
}

int World::getLevelHeight() {
    return 9;
}

void World::makeMove(World::MoveDir) {

}

void World::loadLevels() {
    std::ifstream mapFile("data/map");
    std::string line;
    std::getline(mapFile, line);

}
