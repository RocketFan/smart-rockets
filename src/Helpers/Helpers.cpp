#include "../../include/Helpers/Helpers.h"

float Helpers::map_value(float x, float inMin, float inMax, float outMin, float outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

char Helpers::getRandChar() {
    const std::string printable = "0123456789abcdefghijklmnopqrstuvwxyz ";
    const int index = std::rand() % printable.size();

    return printable[index];
}