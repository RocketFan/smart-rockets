#pragma once

#include <SFML/System.hpp>
#include <cmath>
#include <memory>


template class sf::Vector2<int>;
template class sf::Vector2<unsigned int>;
template class sf::Vector2<float>;

template<typename T>
class Vector2 : public sf::Vector2<T> {
public:
    Vector2(): sf::Vector2<T>() {}

    Vector2(T x, T y): sf::Vector2<T>(x, y) {}

    template<typename U>
    Vector2(const sf::Vector2<U> &vector) : sf::Vector2<T>(vector) {}

    float sqrMagnitude() {
        return std::pow(this->x, 2) + std::pow(this->y, 2);
    }

    float magnitude() {
        return std::sqrt(sqrMagnitude());
    }

    float dot(const Vector2<T> &vector) {
        return this->x * vector.x + this->y * vector.y;
    }

    float cross(const Vector2<T> &vector) {
        return this->x * vector.y - this->y * vector.x;
    }

    void rotate(float angle) {
        angle = (angle / 180) * M_PI;
        T x = this->x;
        T y = this->y;

        this->x = T(std::cos(angle) * x - std::sin(angle) * y);
        this->y = T(std::sin(angle) * x + std::cos(angle) * y);
    }

    void normalize() {
        (*this) = (*this) / this->magnitude();
    }
};

template<typename T>
inline Vector2<T> operator-(const Vector2<T> &right) {
    return Vector2<T>(-right.x, -right.y);
};

template<typename T>
inline Vector2<T> &operator+=(Vector2<T> &left, const Vector2<T> &right) {
    left.x += right.x;
    left.y += right.y;

    return left;
};

template<typename T>
inline Vector2<T> &operator-=(Vector2<T> &left, const Vector2<T> &right) {
    left.x -= right.x;
    left.y -= right.y;

    return left;
};

template<typename T>
inline Vector2<T> operator+(const Vector2<T> &left, const Vector2<T> &right) {
    return Vector2<T>(left.x + right.x, left.y + right.y);
};

template<typename T>
inline Vector2<T> operator-(const Vector2<T> &left, const Vector2<T> &right) {
    return Vector2<T>(left.x - right.x, left.y - right.y);
};

template<typename T>
inline Vector2<T> operator*(const Vector2<T> &left, T right) {
    return Vector2<T>(left.x * right, left.y * right);
};

template<typename T>
inline Vector2<T> operator*(T left, const Vector2<T> &right) {
    return Vector2<T>(right.x * left, right.y * left);
};

template<typename T>
inline Vector2<T> &operator*=(Vector2<T> &left, T right) {
    left.x *= right;
    left.y *= right;

    return left;
};

template<typename T>
inline Vector2<T> operator/(const Vector2<T> &left, T right) {
    return Vector2<T>(left.x / right, left.y / right);
};

template<typename T>
inline Vector2<T> &operator/=(Vector2<T> &left, T right) {
    left.x /= right;
    left.y /= right;

    return left;
};

template<typename T>
inline bool operator==(const Vector2<T> &left, const Vector2<T> &right) {
    return (left.x == right.x) && (left.y == right.y);
};

template<typename T>
inline bool operator!=(const Vector2<T> &left, const Vector2<T> &right) {
    return (left.x != right.x) || (left.y != right.y);
};

typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;