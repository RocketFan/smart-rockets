#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>
#include <future>

#include "Helpers/Vector2.h"
#include "Helpers/PoissonDiskSampling.h"

class AsteroidsManager;
class RocketsManager;
class Rocket;
class GameObject;
class Window;

class Game {
public:
    sf::Event ev;
    std::list<GameObject *> dynamicObjects;
    std::list<GameObject *> staticObjects;
    std::shared_ptr<AsteroidsManager> asteroidsManager;
    std::shared_ptr<RocketsManager> rocketsManager;

    Game();

    void update();

    void render();

    const sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow window;
    std::shared_ptr<class Window> windowShape;
    std::vector<std::future<void>> updateCollisionFutures;

    void initWindow();

    void initAsteroidGenerator();

    void initRockets();

    void updateCollision();

    static void updateCollisionAsync(std::list<GameObject *>::iterator currIter,
                                     std::list<GameObject *>::iterator endIter,
                                     std::list<GameObject *> *staticObjects,
                                     const int iterations = 1);
};