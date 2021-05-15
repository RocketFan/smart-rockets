#include <iostream>
#include "../../include/GameObjects/Rectangle.h"

#include "../../include/Helpers/Collision.h"
#include "../../include/GameObjects/Circle.h"

Rectangle::Rectangle() : GameObject() {
    this->shapeType = ShapeType::Rectangle;
    this->shape = sf::ConvexShape(4);
    this->size = Vector2f();
}

void Rectangle::updateCollision(GameObject *collidedGameObj) {
    bool hit = false;

    if (collidedGameObj->shapeType == ShapeType::Circle) {
        auto circle = (class Circle*) collidedGameObj;

        if(circle->getShape().getGlobalBounds().intersects(shape.getGlobalBounds()))
            hit = Collision::PolyCircle(getPoints(), circle->getPosition(), circle->getRadius());
    }

    this->hit = hit;
    collidedGameObj->hit = hit;
    this->updateOnCollision(collidedGameObj);
    collidedGameObj->updateOnCollision(this);
}

void Rectangle::setSize(Vector2f size) {
    this->size = size;

    setOrigin(Vector2f(size.x / 2, size.y / 2));

    shape.setPoint(0, Vector2f(0, 0));
    shape.setPoint(1, Vector2f(size.x, 0));
    shape.setPoint(2, Vector2f(size.x, size.y));
    shape.setPoint(3, Vector2f(0, size.y));
}

void Rectangle::setRotation(float angle) {
    shape.setRotation(angle);
}

void Rectangle::setOrigin(Vector2f origin) {
    shape.setOrigin(origin);
}

void Rectangle::setColor(sf::Color color) {
    shape.setFillColor(color);
}

std::vector<Vector2f> Rectangle::getPoints() const {
    int len = shape.getPointCount();
    std::vector<Vector2f> points(4);

    for (int i = 0; i < len; i++)
        points[i] = shape.getTransform().transformPoint(shape.getPoint(i));

    return points;
}

const Vector2f &Rectangle::getSize() const {
    return size;
}

const sf::ConvexShape &Rectangle::getShape() {
    shape.setPosition(getPosition());

    return shape;
}

float Rectangle::getRotation() const {
    return shape.getRotation();
}