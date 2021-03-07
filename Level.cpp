//
// Created by deliner on 06.03.2021.
//

#include "Level.h"

Level::Level(int id, int top, int right, int down, int left) {
    this->id = id;
    topDoorLevel = top;
    rightDoorLevel = right;
    downDoorLevel = down;
    leftDoorLevel = left;
}

void Level::load() {

}
