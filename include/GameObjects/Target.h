#pragma once

#include "Circle.h"

class Target : public Circle {
public:
    Target();

    void render(sf::RenderTarget &target);
};