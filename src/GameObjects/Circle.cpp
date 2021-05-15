#include "../../include/GameObjects/Circle.h"

#include "../../include/GameObjects/Rocket.h"
#include "../../include/Helpers/Collision.h"

Circle::Circle() : GameObject() {
    this->shapeType = ShapeType::Circle;
    this->shape = sf::CircleShape();
}

void Circle::updateCollision(GameObject *collidedGameObj) {
    bool hit = false;

    if (collidedGameObj->shapeType == ShapeType::Rectangle) {
        auto rect = (class Rectangle*) collidedGameObj;

        if(rect->getShape().getGlobalBounds().intersects(shape.getGlobalBounds()))
            hit = Collision::PolyCircle(rect->getPoints(), getPosition(), getRadius());
    }

    this->hit = hit;
    collidedGameObj->hit = hit;
    this->updateOnCollision(collidedGameObj);
    collidedGameObj->updateOnCollision(this);
}

void Circle::setRadius(float radius) {
    setOrigin(Vector2f(radius, radius));

    shape.setRadius(radius);
}

void Circle::setOrigin(Vector2f origin) {
    shape.setOrigin(origin);
}

void Circle::setColor(sf::Color color) {
    shape.setFillColor(color);
}

float Circle::getRadius() const {
    return shape.getRadius();
}

const sf::CircleShape & Circle::getShape() {
    shape.setPosition(getPosition());

    return shape;
}