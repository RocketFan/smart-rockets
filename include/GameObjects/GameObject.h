#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>
#include <mutex>

#include "../Enums/ShapeType.h"
#include "../Helpers/Vector2.h"
#include "../Enums/CollisionType.h"
#include "../Enums/GameObjectType.h"

class Game;

class GameObject {
public:
    ShapeType shapeType;
    CollisionType collisionType;
    GameObjectType gameObjectType;
    bool hit = false;

    GameObject();

    ~GameObject();

    virtual void update();

    virtual void updateCollision(GameObject *collidedGameObj) {};

    virtual void updateOnCollision(GameObject *collidedGameObj) {};

    virtual void render(sf::RenderTarget &target) {};

    virtual void onBuild() {};

    void move(Vector2f moveVec);

    void setPosition(Vector2i position);

    void setGame(Game* game);

    const Vector2f &getPosition() const;

protected:
    Game* game;

private:
    Vector2f position;
};
