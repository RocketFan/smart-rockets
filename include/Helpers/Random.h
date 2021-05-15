#pragma once

#include <random>
#include <ctime>

class Random {
public:
    static void Init() {
        s_RandomEngine.seed(time(nullptr));
    }

    static float Float() {
        return (float) s_Distribution(s_RandomEngine) / (float) std::numeric_limits<uint32_t>::max();
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