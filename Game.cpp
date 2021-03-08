//
// Created by deliner on 06.03.2021.
//

#include "Game.h"
#include "SFML/Graphics.hpp"
#include "TextureManager.h"

Game::Game() {
    window = new sf::RenderWindow(sf::VideoMode(800, 450), "cg_task1");
    window->setFramerateLimit(30);

    gameEnded = false;
    gameFinished = false;
    pauseRender = false;

    world = new World(this);


    winTexture = new sf::Texture();
    winTexture->loadFromFile("images/win_screen.png");
    winTexture->setSmooth(true);

    deathTexture = new sf::Texture();
    deathTexture->loadFromFile("images/death_screen.png");
    deathTexture->setSmooth(true);

}

void Game::start() {
    TextureManager::init();
    window->display();
    while (window->isOpen()) {
        updateInput();
        if (!pauseRender) {
            render();
        }
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
                    world->makeMove(MoveDir::UP);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    world->makeMove(MoveDir::LEFT);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    world->makeMove(MoveDir::DOWN);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    world->makeMove(MoveDir::RIGHT);
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

    auto size = window->getSize();
    sf::FloatRect area(0, 0, size.x, size.y);
    window->setView(sf::View(area));

    if (gameEnded || gameFinished) {
        auto sprite = sf::Sprite();
        sprite.setTexture(gameEnded ? *deathTexture : *winTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 800, 450));
        window->draw(sprite);
        pauseRender = true;
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
    pauseRender = false;

    delete world;
    world = new World(this);
}

void Game::onDeath() {
    gameEnded = true;
}

void Game::onFinish() {
    gameFinished = true;
}

