#include "../include/Game.h"

#include <iostream>
#include <future>

#include "../include/GameObjects/GameObjectBuilder.h"
#include "../include/AsteroidsManager.h"
#include "../include/RocketsManager.h"
#include "../include/GameObjects/Rocket.h"
#include "../include/GameObjects/Asteroid.h"
#include "../include/GameObjects/Window.h"

Game::Game() {
    initWindow();
    initRockets();
    initAsteroidGenerator();
}

void Game::update() {
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed)
            window.close();
        else if (ev.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if(rocketsManager->getGenerationCount() % 2 == 0 || rocketsManager->getHitRate() > 0.1)
                asteroidsManager->generate(rocketsManager->spawnPos, 100, 700);

            rocketsManager->updateGeneration();
        }
    }

    if(rocketsManager->checkFinished())
    {
        if(rocketsManager->getGenerationCount() % 2 == 0 || rocketsManager->getHitRate() > 0.1)
            asteroidsManager->generate(rocketsManager->spawnPos, 100, 700);

        rocketsManager->updateGeneration();
    }

    rocketsManager->update(asteroidsManager->target.get());
    updateCollision();
}

void Game::render() {
    window.clear();
    asteroidsManager->render(window);
    rocketsManager->render(window);

    window.display();
}

const sf::RenderWindow &Game::getWindow() const {
    return window;
}

void Game::initWindow() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode(800, 800), "Smart Rockets",
                  sf::Style::Close | sf::Style::Titlebar, settings);
    window.setFramerateLimit(60);

    auto windowSize = window.getSize();

    this->windowShape = GameObjectBuilder<class Window>(this)
            .setPosition(Vector2f (windowSize.x / 2, windowSize.y / 2))
            .build();

    this->windowShape->setSize(window.getSize());
}

void Game::initAsteroidGenerator() {
    auto sampleRegionSize = window.getSize();
    auto center = Vector2i(sampleRegionSize) / 2;

    this->asteroidsManager = std::make_shared<AsteroidsManager>(this, sampleRegionSize, center,
                                                                40, 10, 50);

    asteroidsManager->generate(rocketsManager->spawnPos, 100, 700);
}

void Game::initRockets() {
    auto windowSize = window.getSize();
    auto spawnPos = Vector2f(windowSize.x / 2, windowSize.y - 50);
    auto rocketSize = Vector2u(10, 20);

    this->rocketsManager = std::make_shared<RocketsManager>(this, rocketSize, spawnPos);
}

void Game::updateCollision() {
    updateCollisionFutures.clear();

//    std::cout << dynamicObjects.size() << " " << staticObjects.size() << std::endl;

    const int iterations = 30;
    auto it = dynamicObjects.begin();
    if (dynamicObjects.size() >= iterations * 3 && false) {
        int i = 0;

        while (it != dynamicObjects.end()) {
            if (i % iterations == 0)
                updateCollisionFutures.push_back(std::async(updateCollisionAsync,
                                                            it, dynamicObjects.end(), &staticObjects, iterations));

            it++;
            i++;
        }
    } else {
        while (it != dynamicObjects.end()) {
            updateCollisionAsync(it, dynamicObjects.end(), &staticObjects);

            it++;
        }
    }

//    for (const auto &future: updateCollisionFutures)
//        future.wait();
}

void Game::updateCollisionAsync(std::list<GameObject *>::iterator currIter, std::list<GameObject *>::iterator endIter,
                                std::list<GameObject *> *staticObjects, const int iterations) {

    int i = 0;

    while (i < iterations && currIter != endIter) {
        for (auto jt = std::next(currIter); jt != endIter; jt++) {
            (*currIter)->updateCollision(*jt);
        }

        for (auto &jt : (*staticObjects)) {
            (*currIter)->updateCollision(jt);
        }

        i++;
        currIter++;
    }
}