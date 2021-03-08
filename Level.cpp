//
// Created by deliner on 06.03.2021.
//

#include "Level.h"

const char Level::WALL = '#';
const char Level::KEY = 'K';
const char Level::GRASS = '.';
const char Level::EMPTY = ' ';
const char Level::DOOR = 'd';
const char Level::DOOR_OPEN = 'D';
const char Level::PLAYER = '@';
const char Level::FINISH = 'F';


Level::Level(Callback *callback, int id, int top, int right, int down, int left, std::vector<std::vector<char>> *map) {
    this->callback = callback;
    this->id = id;
    topDoorLevel = top;
    rightDoorLevel = right;
    downDoorLevel = down;
    leftDoorLevel = left;
    this->map = map;

    findDoorPositions();

    if (id == 1) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 16; j++) {
                if ((*map)[i][j] == PLAYER) {
                    playerPos = std::pair<int, int>(i, j);
                    (*map)[i][j] = GRASS;
                    return;
                }
            }
        }
    }
}

void Level::findDoorPositions() {
    if (topDoorLevel != 0) {
        for (int i = 0; i < 16; i++) {
            if ((*map)[0][i] == DOOR) {
                topDoorPosition = std::pair<int, int>(0, i);
                return;
            }
        }
    }
    if (downDoorLevel != 0) {
        for (int i = 0; i < 16; i++) {
            if ((*map)[8][i] == DOOR) {
                downDoorPosition = std::pair<int, int>(9, i);
                return;
            }
        }
    }
    if (rightDoorLevel != 0) {
        for (int i = 0; i < 9; i++) {
            if ((*map)[i][15] == DOOR) {
                rightDoorPosition = std::pair<int, int>(i, 16);
                return;
            }
        }
    }
    if (leftDoorLevel != 0) {
        for (int i = 0; i < 9; i++) {
            if ((*map)[i][0] == DOOR) {
                leftDoorPosition = std::pair<int, int>(i, 0);
                return;
            }
        }
    }
}

void Level::makeMove(MoveDir dir) {
    if (dir == MoveDir::UP) {
        onNewPos(std::pair<int, int>(playerPos.first, playerPos.second - 1));
    } else if (dir == MoveDir::RIGHT) {
        onNewPos(std::pair<int, int>(playerPos.first + 1, playerPos.second));
    } else if (dir == MoveDir::DOWN) {
        onNewPos(std::pair<int, int>(playerPos.first, playerPos.second + 1));
    } else if (dir == MoveDir::LEFT) {
        onNewPos(std::pair<int, int>(playerPos.first - 1, playerPos.second));
    }
}

void Level::onNewPos(std::pair<int, int> newPos) {
    if ((*map)[newPos.first][newPos.second] == GRASS) {
        playerPos = newPos;
    } else if ((*map)[newPos.first][newPos.second] == KEY) {
        (*map)[newPos.first][newPos.second] = GRASS;
        callback->getPlayerKeys()++;
        playerPos = newPos;
    } else if ((*map)[newPos.first][newPos.second] == EMPTY) {
        callback->playerDied();
    } else if (newPos == topDoorPosition) {
        onDoorEntry(newPos, topDoorLevel);
    } else if (newPos == rightDoorPosition) {
        onDoorEntry(newPos, rightDoorLevel);
    } else if (newPos == downDoorPosition) {
        onDoorEntry(newPos, downDoorLevel);
    } else if (newPos == leftDoorPosition) {
        onDoorEntry(newPos, leftDoorLevel);
    } else if ((*map)[newPos.first][newPos.second] == FINISH) {
        callback->playerFinished();
    }
}

void Level::onDoorEntry(std::pair<int, int> newPos, int levelId) {
    if ((*map)[newPos.first][newPos.second] == DOOR) {
        if (callback->getPlayerKeys() > 0) {
            callback->getPlayerKeys()--;
            (*map)[newPos.first][newPos.second] = DOOR_OPEN;
        } else {
            return;
        }
    }
    callback->loadLevel(levelId);
}

void Level::setPlayerFromLevel(int levelId) {
    std::pair<int, int> bufPos;
    if (levelId == topDoorLevel) {
        bufPos = topDoorPosition;
    } else if (levelId == rightDoorLevel) {
        bufPos = rightDoorPosition;
    } else if (levelId == downDoorLevel) {
        bufPos = downDoorPosition;
    } else if (levelId == leftDoorLevel) {
        bufPos = leftDoorPosition;
    }
    if ((*map)[bufPos.first][bufPos.second] == DOOR) {
        (*map)[bufPos.first][bufPos.second] = DOOR_OPEN;
    }
    playerPos = bufPos;
}