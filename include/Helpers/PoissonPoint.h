#pragma once

#include <SFML/System.hpp>
#include <cmath>

#include "Vector2.h"

class PoissonPoint {
public:
    Vector2i position;
    float radius;

    PoissonPoint(Vector2i position, float radius);

    int getGridsToSearch(float cellSize, float offset, float maxRadius) const;
};