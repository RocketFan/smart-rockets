#include "../../include/GameObjects/Window.h"

#include <iostream>

#include "../../include/GameObjects/Ray.h"

Window::Window() {
    this->collisionType = CollisionType::Dynamic;
    this->gameObjectType = GameObjectType::Window;
}

void Window::updateCollision(GameObject *collidedGameObj) {
    bool hit = false;
    auto windowBounds = getShape().getGlobalBounds();

    if(collidedGameObj->shapeType == ShapeType::Rectangle) {
        auto rectBounds = ((class Rectangle*)collidedGameObj)->getShape().getGlobalBounds();

        if(rectBounds.top < windowBounds.top)
            hit = true;
        else if(rectBounds.top + rectBounds.height > windowBounds.top + windowBounds.height)
            hit = true;
        else if(rectBounds.left < windowBounds.left)
            hit = true;
        else if(rectBounds.left + rectBounds.width > windowBounds.left + windowBounds.width)
            hit = true;
    } else if(collidedGameObj->gameObjectType == GameObjectType::Ray) {
        auto ray = (class Ray*) collidedGameObj;

        ray->updateCollision(this);
    }

    this->hit = hit;
    collidedGameObj->hit = hit;
    collidedGameObj->updateOnCollision(this);
}