#include "../../include/Helpers/PoissonPoint.h"

PoissonPoint::PoissonPoint(Vector2i position, float radius) {
    this->position = position;
    this->radius = radius;
}

int PoissonPoint::getGridsToSearch(float cellSize, float offset, float maxRadius) const {
    return int((radius + offset + maxRadius) / cellSize) + 1;
}