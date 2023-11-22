#pragma once

#include <random>
#include <ctime>
#include <iostream>

class Random {
public:
    static void Init() {
        s_RandomEngine.seed(time(nullptr));
    }

    static float Float() {
        return std::generate_canonical<float, std::numeric_limits<float>::digits>(s_RandomEngine);
    }

    static float RangeFloat(float min, float max) {
        return Float() * (max - min) + min;
    }

    static int RangeInt(int min, int max) {
        return int(Float() * (max - min) + min);
    }

private:
    static std::mt19937 s_RandomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};