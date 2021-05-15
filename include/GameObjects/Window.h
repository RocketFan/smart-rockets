#pragma once

#include "Rectangle.h"

class Window : public Rectangle {
public:
    Window();

    void updateCollision(GameObject *collidedGameObj);
};