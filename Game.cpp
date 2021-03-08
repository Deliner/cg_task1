//
// Created by deliner on 06.03.2021.
//

#include "Game.h"
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

Game::Game() {
    window = new sf::RenderWindow(sf::VideoMode(800, 450), "cg_task1");
    window->setFramerateLimit(30);
    window->setVerticalSyncEnabled(true);

    gameEnded = false;
    gameFinished = false;

    world = new World(this);

}

void Game::start() {
    TextureManager::init();
    window->display();
    while (window->isOpen()) {
        updateInput();
        render();
    }
}

void Game::updateInput() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (!gameFinished && !gameEnded) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    world->makeMove(MoveDir::LEFT);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    world->makeMove(MoveDir::UP);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    world->makeMove(MoveDir::RIGHT);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    world->makeMove(MoveDir::DOWN);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (gameEnded) {
                    reset();
                } else if (gameFinished) {
                    window->close();
                }
            }
        }
    }
}

void Game::render() {
    window->clear();
    world->updateTiles();

    if (gameEnded) {

    } else if (gameFinished) {

    } else {
        for (int i = 0; i < world->getLevelHeight(); i++) {
            for (int j = 0; j < world->getLevelWidth(); j++) {
                window->draw(world->tiles[i][j]->sprite);
            }
        }
    }
    window->display();
}

void Game::reset() {
    gameEnded = false;
    gameFinished = false;

    world = new World(this);
}

void Game::onDeath() {
    gameEnded = true;
}

void Game::onFinish() {
    gameFinished = true;
}

