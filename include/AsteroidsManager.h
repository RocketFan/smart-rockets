#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <memory>

#include "Helpers/PoissonDiskSampling.h"
#include "Helpers/Vector2.h"
#include "GameObjects/Target.h"

template<typename T>
class GameObjectBuilder;
class Asteroid;
class GameObject;
class Game;

class AsteroidsManager {
public:
    std::shared_ptr<class Target> target;

    AsteroidsManager(Game *game, Vector2u sampleRegionSize, Vector2i center,
                     float offset, float minRadius, float maxRadius);

    void generate(Vector2f rocketsSpawnPos, float radiusOffset, float minDistance);

    void update();

    void render(sf::RenderTarget &target);

    void removeAsteroid(class Asteroid* asteroid);

    void removeAsteroidsInRadius(Vector2f center, float radius);

private:
    std::vector<std::shared_ptr<class Asteroid>> asteroids;
    std::shared_ptr<PoissonDiskSampling> sampling;
    Game* game;
};