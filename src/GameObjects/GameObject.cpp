#include <iostream>
#include "../../include/GameObjects/GameObject.h"

#include "../../include/Game.h"

GameObject::GameObject() {
    this->shapeType = ShapeType::None;
    this->gameObjectType = GameObjectType::NoneType;
    this->position = Vector2i();
}

GameObject::~GameObject() {
    if(collisionType == CollisionType::Static)
        game->staticObjects.remove(this);
    if(collisionType == CollisionType::Dynamic)
        game->dynamicObjects.remove(this);
}

void GameObject::update() {}

void GameObject::move(Vector2f moveVec) {
    position += moveVec;
}

void GameObject::setGame(Game *game) {
    this->game = game;

    if(collisionType == CollisionType::Static)
        game->staticObjects.push_back(this);
    else if(collisionType == CollisionType::Dynamic)
        game->dynamicObjects.push_back(this);
}

void GameObject::setPosition(Vector2i position) {
    this->position = position;
};

const Vector2f &GameObject::getPosition() const {
    return position;
}