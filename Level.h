//
// Created by deliner on 06.03.2021.
//

#ifndef CG_TASK1_LEVEL_H
#define CG_TASK1_LEVEL_H


#include <utility>
#include <vector>
#include "Utils.h"

struct Level {

    class Callback;

    Level(Callback *callback, int id, int top, int right, int down, int left, std::vector<std::vector<char>> *);

    int topDoorLevel;
    int rightDoorLevel;
    int downDoorLevel;
    int leftDoorLevel;

    std::pair<int, int> topDoorPosition;
    std::pair<int, int> rightDoorPosition;
    std::pair<int, int> downDoorPosition;
    std::pair<int, int> leftDoorPosition;

    int id;

    std::pair<int, int> playerPos;

    std::vector<std::vector<char>> *map;

    void setPlayerFromLevel(int);

    void makeMove(MoveDir);

    static const char WALL;
    static const char KEY;
    static const char GRASS;
    static const char EMPTY;
    static const char DOOR;
    static const char DOOR_OPEN;
    static const char PLAYER;
    static const char FINISH;


private:
    Callback *callback;

    void onNewPos(std::pair<int, int> newPos);

    void findDoorPositions();

    void onDoorEntry(std::pair<int, int> newPos, int id);
};


class Level::Callback {

public:
    virtual int &getPlayerKeys() = 0;

    virtual void loadLevel(int) = 0;

    virtual void playerFinished() = 0;

    virtual void playerDied() = 0;
};


#endif //CG_TASK1_LEVEL_H
