#include "../../include/GameObjects/Target.h"

Target::Target() {
    this->collisionType = CollisionType::Static;
    this->gameObjectType = GameObjectType::Target;
    setColor(sf::Color::Red);
}

void Target::render(sf::RenderTarget &target) {
    target.draw(getShape());
}