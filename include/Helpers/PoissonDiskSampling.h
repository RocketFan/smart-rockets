#pragma once

#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <thread>
#include <mutex>

#include "PoissonPoint.h"
#include "Helpers.h"
#include "Random.h"
#include "Vector2.h"

class PoissonDiskSampling {
public:
    PoissonDiskSampling(Vector2u sampleRegionSize, Vector2i center, float offset,
                        float minRadius, float maxRadius, int numSamplesBeforeRejection = 30);

    std::vector<std::shared_ptr<PoissonPoint>> generatePoints();

private:
    Vector2u sampleRegionSize;
    Vector2i center;
    float offset;
    float minRadius;
    float maxRadius;
    float cellSize;
    int numSamplesBeforeRejection;
    std::vector<std::vector<int>> grid;
    std::vector<std::shared_ptr<PoissonPoint>> points;
    std::vector<std::shared_ptr<PoissonPoint>> spawnPoints;

    void initPoints();

    bool isValid(const std::shared_ptr<PoissonPoint> &candidate);

    bool isInsideRegion(Vector2i pointPos, float pointRadius);
};