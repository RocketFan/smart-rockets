#include "../include/RocketsManager.h"

#include "../include/Game.h"
#include "../include/GameObjects/GameObjectBuilder.h"
#include "../include/GameObjects/Rocket.h"
#include "../include/GameObjects/Target.h"
#include <chrono>

RocketsManager::RocketsManager(Game *game, Vector2u rocketSize, Vector2f spawnPos) {
    this->game = game;
    this->spawnPos = spawnPos;

    rockets.clear();
    int nRays = 10;
    int fieldOfView = 140;

    for (int i = 0; i < 60; i++) {
        auto rocket = GameObjectBuilder<class Rocket>(game)
                .setPosition(spawnPos)
                .build();

        rocket->setSize(rocketSize);
        rocket->setRays(nRays, fieldOfView);
        this->rockets.push_back(rocket);
    }

    std::vector<int> size{5 + nRays, 16, 32, 2};

    this->population = std::make_shared<Population>(size, 0.01, rockets.size());
    population->setDNAToRockets(rockets);
    this->time = std::chrono::high_resolution_clock::now();
}

void RocketsManager::update(class Target *target) {
    for (const auto &rocket: rockets) {
        rocket->setTarget(target);
        rocket->update();
    }
}

void RocketsManager::render(sf::RenderTarget &target) {
    for (const auto &rocket: rockets)
        rocket->render(target);
}

void RocketsManager::updateGeneration() {
    for(auto &rocket : rockets) {
        rocket->reset(spawnPos);
    }

    population->naturalSelection();
    population->generate();
    population->setDNAToRockets(rockets);

    this->time = std::chrono::high_resolution_clock::now();
}

bool RocketsManager::checkFinished() {
    bool finished = true;

    for(const auto& rocket : rockets)
        if(!rocket->stop)
            finished = false;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - time;
    if (elapsed.count() > 12.0)
        finished = true;

    return finished;
}

int RocketsManager::getGenerationCount() const {
    return population->generations;
}

float RocketsManager::getHitRate() const {
    int hitCount = 0;

    for(const auto& rocket : rockets)
        if(rocket->getHitTarget())
            hitCount += 1;

    return hitCount / rockets.size();
}