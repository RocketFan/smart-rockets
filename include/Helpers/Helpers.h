#pragma once

#include <SFML/System.hpp>
#include <string>
#include <cmath>

class Helpers {
public:
    static float map_value(float x, float inMin, float inMax, float outMin, float outMax);

    static char getRandChar();

private:
    Helpers();
};