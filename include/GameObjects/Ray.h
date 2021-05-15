#pragma once

#include "GameObject.h"

class Ray : public GameObject {
public:
    Ray();

    void update();

    void updateCollision(GameObject *collidedGameObj);

    void render(sf::RenderTarget &target);

    void onBuild();

    void rotate(float angle);

    void setMaxDistance(float maxDistance);

    float getDistance() const;

    const Vector2f& getPoint() const;

private:
    Vector2f dir = Vector2f(0, -1);
    Vector2f point;
    float distance;
    float maxDistance = 200;
};