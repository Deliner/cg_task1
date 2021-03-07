//
// Created by deliner on 06.03.2021.
//

#ifndef CG_TASK1_WORLD_H
#define CG_TASK1_WORLD_H


#include <vector>
#include "GameTile.h"

class World {

public:
    class Callback;

    World(Callback *);

    enum MoveDir {
        UP, RIGHT, DOWN, LEFT
    };

    std::vector<std::vector<GameTile *>> tiles;

    void makeMove(MoveDir);

    int getLevelHeight();

    int getLevelWidth();

private:
    Callback *callback;

    int levelHeight;
    int levelWidth;

    int playerKeys;

    void loadLevels();

};

class World::Callback {
public:
    virtual void onDeath() = 0;
    virtual void onFinish() = 0;
};

#endif //CG_TASK1_WORLD_H
