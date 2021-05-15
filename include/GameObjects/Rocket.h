#pragma once

// To neural network
// 0 - dir.x, 1 - dir.y, 2 - targetDir.x, 3 - targetDir.y, 4 - targetDist, and rays distances

// From neural network:
// 0 - vel, 1 - diffAngle

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../Helpers/Vector2.h"
#include "../Helpers/Matrix.h"
#include "Rectangle.h"

class Ray;
class GameObject;
class DNA;
class Target;

class Rocket : public Rectangle {
public:
    bool stop = false;

    Rocket();

    void update();

    void updateCollision(GameObject *collidedGameObj);

    void updateOnCollision(GameObject *collidedGameObj);

    void render(sf::RenderTarget &target);

    void reset(Vector2f spawnPos);

    void setRays(int nRays, float fieldOfView);

    void setDNA(DNA *dna);

    void setTarget(class Target *target);

    bool getHitTarget() const;

private:
    DNA *dna;
    std::shared_ptr<Matrix> inputs;
    std::vector<std::shared_ptr<class Ray>> rays;
    Vector2f dir = Vector2f(0, -1);
    float vel = 2;
    float fieldOfView;

    void createRays();
};