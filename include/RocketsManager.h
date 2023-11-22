#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "Helpers/Vector2.h"
#include "GeneticAlgorithm/Population.h"

class Rocket;
class Game;

class RocketsManager {
public:
    Vector2f spawnPos;
    std::chrono::high_resolution_clock::time_point time;

    RocketsManager(Game* game, Vector2u rocketSize, Vector2f spawnPos);

    void update(class Target* target);

    void render(sf::RenderTarget &target);

    void updateGeneration();

    bool checkFinished();

    int getGenerationCount() const;

    float getHitRate() const;

private:
    std::vector<std::shared_ptr<class Rocket>> rockets;
    std::shared_ptr<Population> population;
    Game* game;
};