#include "../include/AsteroidsManager.h"

#include <iostream>

#include "../include/GameObjects/GameObjectBuilder.h"
#include "../include/GameObjects/Asteroid.h"
#include "../include/Helpers/Collision.h"
#include "../include/Game.h"

AsteroidsManager::AsteroidsManager(Game *game,
                                   Vector2u sampleRegionSize, Vector2i center,
                                   float offset, float minRadius, float maxRadius)
        : game(game) {

    this->sampling = std::make_shared<PoissonDiskSampling>(sampleRegionSize, center, offset, minRadius, maxRadius);
}

void AsteroidsManager::generate(Vector2f rocketsSpawnPos, float radiusOffset, float minDistance) {
    auto points = sampling->generatePoints();
    std::shuffle(points.begin(), points.end(), std::default_random_engine{});

    this->target = nullptr;

    for(int i = 0; i < points.size(); i++) {
        float sqrDistance = (Vector2f (points[i]->position) - rocketsSpawnPos).sqrMagnitude();

        if(sqrDistance > minDistance * minDistance)
        {
            this->target = GameObjectBuilder<class Target>(game)
                    .setPosition(points[i]->position)
                    .build();

            this->target->setRadius(points[i]->radius);

            points.erase(points.begin() + i);
            break;
        }
    }

    if(!target) {
        auto center = game->getWindow().getSize() / 2u;
        float radius = 20;

        this->target = GameObjectBuilder<class Target>(game)
                .setPosition(center)
                .build();

        this->target->setRadius(radius);

        removeAsteroidsInRadius(center, radius * 2);
    }

    asteroids.clear();

    for (const auto &point : points) {
        auto asteroid = GameObjectBuilder<class Asteroid>(game)
                .setPosition(point->position)
                .build();

        asteroid->setRadius(point->radius);
        asteroid->setManager(this);

        asteroids.push_back(asteroid);
    }

    removeAsteroidsInRadius(rocketsSpawnPos, radiusOffset);
}

void AsteroidsManager::render(sf::RenderTarget &target) {
    for (const auto &asteroid : asteroids)
        asteroid->render(target);

    this->target->render(target);
}

void AsteroidsManager::removeAsteroid(class Asteroid *asteroid) {
    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [&](auto const &a) {
        return a.get() == asteroid;
    }), asteroids.end());

    std::cout << asteroids.size() << std::endl;
}

void AsteroidsManager::removeAsteroidsInRadius(Vector2f center, float radius) {
    for (int i = 0; i < asteroids.size(); i++) {
        if (Collision::CircleCircle(center, radius, asteroids[i]->getPosition(),
                                    asteroids[i]->getRadius())) {

            asteroids.erase(asteroids.begin() + i);
            i--;
        }
    }
}