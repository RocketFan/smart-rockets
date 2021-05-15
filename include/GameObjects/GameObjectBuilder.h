#pragma once

#include <list>
#include <memory>

#include "../Enums/ShapeType.h"
#include "../Helpers/Vector2.h"

class GameObject;
class Game;

template<typename T>
class GameObjectBuilder {
public:
    GameObjectBuilder(Game* game) {
        gameObject->setGame(game);
    }

    std::shared_ptr<T> build() {
        gameObject->onBuild();

        return gameObject;
    };

    GameObjectBuilder<T> &setCollisionType(ShapeType collisionType) {
        gameObject->setCollisionType(collisionType);

        return *this;
    };

    GameObjectBuilder<T> &setPosition(Vector2i position) {
        gameObject->setPosition(position);

        return *this;
    };

private:
    std::shared_ptr<T> gameObject = std::make_shared<T>();
};