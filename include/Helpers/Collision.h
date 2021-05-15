#pragma once

#include <vector>

#include "Vector2.h"

namespace Collision {
    bool PolyCircle(const std::vector<Vector2f> &polygon, Vector2f circleCenter, float radius);

    bool LineCircle(Vector2f start, Vector2f end, Vector2f circleCenter, float radius);

    bool CircleCircle(Vector2f c1, float r1, Vector2f c2, float r2);

    bool PointCircle(Vector2f point, Vector2f circleCenter, float radius);

    bool LinePoint(Vector2f start, Vector2f end, Vector2f point);

    float RayCircle(Vector2f rayStart, Vector2f dir, Vector2f circleCenter, float radius);

    float RayPoly(Vector2f rayStart, Vector2f dir, float maxDistance, const std::vector<Vector2f> &polygon);

    float RayLine(Vector2f a, Vector2f b, Vector2f c, Vector2f d);

}