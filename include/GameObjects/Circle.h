#pragma once

#include <SFML/Graphics.hpp>

#include "../Enums/ShapeType.h"
#include "GameObject.h"

class Game;

class Circle : public GameObject {
public:
    Circle();

    virtual void update() {}

    virtual void updateCollision(GameObject *collidedGameObj);

    virtual void updateOnCollision(GameObject *collidedGameObj) {}

    virtual void render(sf::RenderTarget &target) {}

    virtual void onBuild() {}

    void setRadius(float radius);

    void setOrigin(Vector2f origin);

    void setColor(sf::Color color);

    float getRadius() const;

    const sf::CircleShape &getShape();

private:
    sf::CircleShape shape;
};