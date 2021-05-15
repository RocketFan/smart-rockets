#include "../../include/GameObjects/Ray.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../../include/Helpers/Collision.h"
#include "../../include/GameObjects/Circle.h"
#include "../../include/GameObjects/Window.h"

Ray::Ray() : GameObject() {
    this->collisionType = CollisionType::Dynamic;
    this->gameObjectType = GameObjectType::Ray;
}

void Ray::update() {
    this->distance = maxDistance;
    this->point = getPosition() + dir * maxDistance;
}

void Ray::updateCollision(GameObject *collidedGameObj) {
    float currDistance = -1;

    if (collidedGameObj->shapeType == ShapeType::Circle) {
        auto circle = (class Circle *) collidedGameObj;

        currDistance = Collision::RayCircle(getPosition(), dir, circle->getPosition(), circle->getRadius());
    } else if (collidedGameObj->gameObjectType == GameObjectType::Window) {
        auto window = (class Window *) collidedGameObj;

        currDistance = Collision::RayPoly(getPosition(), dir, maxDistance, window->getPoints());
    }

    if (currDistance >= 0 && currDistance < distance) {
        this->distance = currDistance;
        this->point = getPosition() + dir * distance;
    }
}

void Ray::render(sf::RenderTarget &target) {
    float radius = 4;
    sf::CircleShape closestPoint(radius);
    closestPoint.setPosition(point.x - radius, point.y - radius);
    closestPoint.setFillColor(sf::Color::Red);

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = getPosition();
    line[0].color = sf::Color::Green;
    line[1].position = point;
    line[1].color = sf::Color::Green;

    target.draw(line);
    target.draw(closestPoint);
}

void Ray::rotate(float angle) {
    this->dir.rotate(angle);
}

void Ray::onBuild() {
    this->distance = maxDistance;
    this->point = getPosition() + dir * maxDistance;
}

void Ray::setMaxDistance(float maxDistance) {
    this->maxDistance = maxDistance;
}

float Ray::getDistance() const {
    return distance / maxDistance;
}