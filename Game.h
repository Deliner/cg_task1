//
// Created by deliner on 06.03.2021.
//

#ifndef CG_TASK1_GAME_H
#define CG_TASK1_GAME_H

#include "SFML/Graphics.hpp"
#include "World.h"

class Game : public World::Callback {


public:
    Game();

    void start();

private:
    sf::RenderWindow *window;
    World *world;

    bool gameEnded;
    bool gameFinished;
    bool pauseRender;

    sf::Texture *winTexture;
    sf::Texture *deathTexture;

    void updateInput();

    void render();

    void reset();

    void onDeath() override;

    void onFinish() override;

};


#endif //CG_TASK1_GAME_H
