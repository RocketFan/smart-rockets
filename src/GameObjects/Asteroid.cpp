#include "../../include/GameObjects/Asteroid.h"

#include "../../include/AsteroidsManager.h"

Asteroid::Asteroid() : Circle() {
    this->collisionType = CollisionType::Static;
    this->gameObjectType = GameObjectType::Asteroid;
}

void Asteroid::render(sf::RenderTarget &target) {
    target.draw(getShape());
}

void Asteroid::setManager(AsteroidsManager *asteroidsManager) {
    this->manager = asteroidsManager;
}