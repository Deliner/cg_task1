//
// Created by deliner on 06.03.2021.
//

#ifndef CG_TASK1_WORLD_H
#define CG_TASK1_WORLD_H


#include <vector>
#include "GameTile.h"
#include "Level.h"
#include "Utils.h"

class World : public Level::Callback {

public:
    class Callback;

    explicit World(World::Callback *);

    std::vector<std::vector<GameTile *>> tiles;

    void makeMove(MoveDir);

    int getLevelHeight();

    int getLevelWidth();

    void updateTiles();

private:
    Callback *callback;

    int playerKeys;

    std::vector<Level *> levels;
    Level *currentLevel;

    void loadLevels();

    Level *getLevelFromLine(std::string);

    std::vector<std::vector<char>> *getMapFromFile(int id);

    int &getPlayerKeys() override;

    void loadLevel(int) override;

    void playerFinished() override;

    void playerDied() override;

    void setTiles();

    sf::Texture *charToTexture(char tile);
};

class World::Callback {
public:
    virtual void onDeath() = 0;

    virtual void onFinish() = 0;
};

#endif //CG_TASK1_WORLD_H
