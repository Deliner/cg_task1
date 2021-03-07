//
// Created by deliner on 06.03.2021.
//

#ifndef CG_TASK1_LEVEL_H
#define CG_TASK1_LEVEL_H


#include <utility>
#include <vector>

struct Level {

    Level(int id, int top, int right, int down, int left);

    int topDoorLevel;
    int rightDoorLevel;
    int downDoorLevel;
    int leftDoorLevel;

    int width;
    int height;

    int id;

    std::pair<int, int> playerPos;

    std::vector<std::vector<char>> map;

    void load();
};


#endif //CG_TASK1_LEVEL_H
