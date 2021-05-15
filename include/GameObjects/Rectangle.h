#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../Enums/ShapeType.h"
#include "../Helpers/Vector2.h"
#include "GameObject.h"

class Rectangle : public GameObject {
public:
    Rectangle();

    virtual void update() {};

    virtual void updateCollision(GameObject *collidedGameObj);

    virtual void updateOnCollision(GameObject *collidedGameObj) {};

    virtual void render(sf::RenderTarget &target) {};

    virtual void onBuild() {}

    void setSize(Vector2f size);

    void setRotation(float angle);

    void setOrigin(Vector2f origin);

    void setColor(sf::Color color);

    const Vector2f &getSize() const;

    const sf::ConvexShape &getShape();

    float getRotation() const;

    std::vector<Vector2f> getPoints() const;

private:
    sf::ConvexShape shape;
    Vector2f size;
};