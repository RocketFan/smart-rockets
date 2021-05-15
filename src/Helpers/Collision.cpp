#include "../../include/Helpers/Collision.h"

#include <limits>

bool Collision::PolyCircle(const std::vector<Vector2f> &polygon, Vector2f circleCenter, float radius) {
    int next = 0;

    for (int curr = 0; curr < polygon.size(); curr++) {
        if (++next == polygon.size())
            next = 0;

        auto start = polygon[curr];
        auto end = polygon[next];

        if (LineCircle(start, end, circleCenter, radius))
            return true;
    }

    return false;
}

bool Collision::LineCircle(Vector2f start, Vector2f end, Vector2f circleCenter, float radius) {
    if (PointCircle(start, circleCenter, radius) || PointCircle(start, circleCenter, radius))
        return true;

    auto lineVector = end - start;
    float len = lineVector.magnitude();

    float dot = ((circleCenter.x - start.x) * lineVector.x + (circleCenter.y - start.y) * lineVector.y)
                / std::pow(len, 2);

    auto closestPoint = start + (dot * lineVector);

    if (!LinePoint(start, end, closestPoint))
        return false;

    float distance = (closestPoint - circleCenter).sqrMagnitude();

    if (distance <= radius * radius)
        return true;

    return false;
}

bool Collision::CircleCircle(Vector2f c1, float r1, Vector2f c2, float r2) {
    float distance = (c2 - c1).sqrMagnitude();

    if(distance <= (r1 + r2) * (r1 + r2))
        return true;

    return false;
}

bool Collision::PointCircle(Vector2f point, Vector2f circleCenter, float radius) {
    float distance = (circleCenter - point).sqrMagnitude();

    if (distance <= radius * radius)
        return true;

    return false;
}

bool Collision::LinePoint(Vector2f start, Vector2f end, Vector2f point) {
    float d1 = (point - start).magnitude();
    float d2 = (point - end).magnitude();

    float lineLen = (end - start).magnitude();
    float buffer = 0.01;

    if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer)
        return true;

    return false;
}

float Collision::RayCircle(Vector2f rayStart, Vector2f dir, Vector2f circleCenter, float radius) {
    auto diff = circleCenter - rayStart;
    bool isInside = PointCircle(rayStart, circleCenter, radius);

    if(isInside)
            dir *= -1.f;

    float dot = dir.dot(diff);
    float h2 = diff.sqrMagnitude() - std::pow(dot, 2);

    if(h2 <= radius * radius) {
        float distance = dot - std::sqrt(std::pow(radius, 2) - h2);

        if(distance < 0 && !isInside)
            return -1;

        return std::abs(distance);
    }

    return -1;
}

float Collision::RayPoly(Vector2f rayStart, Vector2f dir, float maxDistance, const std::vector<Vector2f> &polygon) {
    auto a = rayStart;
    auto b = rayStart + dir * maxDistance;
    int next = 0;
    bool found = false;
    float minDistance = std::numeric_limits<float>::max();

    for (int curr = 0; curr < polygon.size(); curr++) {
        if (++next == polygon.size())
            next = 0;

        auto c = polygon[curr];
        auto d = polygon[next];
        float distance = RayLine(a, b, c, d);

        if(distance < minDistance && distance >= 0) {
            found = true;
            minDistance = distance;
        }
    }

    return found ? minDistance : -1;
}

float Collision::RayLine(Vector2f a, Vector2f b, Vector2f c, Vector2f d) {
    auto r = (b - a);
    auto s = (d - c);

    float cross = r.cross(s);

    if(cross == 0)
        return -1;

    float t = ((c.x - a.x) * s.y - (c.y - a.y) * s.x) / cross;
    float u = ((c.x - a.x) * r.y - (c.y - a.y) * r.x) / cross;

    if(t >= 0 && t <= 1 && u >= 0 && u <= 1)
        return r.magnitude() * t;

    return -1;
}