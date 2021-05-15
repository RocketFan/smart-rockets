#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "../Helpers/Vector2.h"
#include "Circle.h"

class AsteroidsManager;
class GameObject;
class Game;

class Asteroid : public Circle {
public:
    Asteroid();

    void render(sf::RenderTarget &target);

    void setManager(AsteroidsManager* manager);

private:
    AsteroidsManager* manager;
};