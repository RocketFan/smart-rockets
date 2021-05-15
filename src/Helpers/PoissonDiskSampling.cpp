#include "../../include/Helpers/PoissonDiskSampling.h"

PoissonDiskSampling::PoissonDiskSampling(Vector2u sampleRegionSize, Vector2i center, float offset,
                                         float minRadius, float maxRadius, int numSamplesBeforeRejection) {

    this->sampleRegionSize = sampleRegionSize;
    this->center = center - Vector2i(sampleRegionSize) / 2;
    this->offset = offset;
    this->minRadius = minRadius;
    this->maxRadius = maxRadius;
    this->numSamplesBeforeRejection = numSamplesBeforeRejection;
    this->cellSize = minRadius / std::sqrt(2);
    int gridSizeX = int(std::ceil(sampleRegionSize.x / cellSize));
    int gridSizeY = int(std::ceil(sampleRegionSize.y / cellSize));
    this->grid = std::vector<std::vector<int>>(gridSizeX, std::vector<int>(gridSizeY, 0));
}

void PoissonDiskSampling::initPoints() {
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            grid[i][j] = 0;

    points.clear();
    spawnPoints.clear();

    Vector2i startPoint(sampleRegionSize.x / 2, sampleRegionSize.y / 2);
    spawnPoints.push_back(std::make_shared<PoissonPoint>(startPoint, minRadius));
}

std::vector<std::shared_ptr<PoissonPoint>> PoissonDiskSampling::generatePoints() {
    initPoints();

    while (!spawnPoints.empty()) {
        int spawnIndex = Random::RangeInt(0, spawnPoints.size());
        auto spawnPoint = spawnPoints[spawnIndex];
        bool candidateAccepted = false;

        for (int i = 0; i < numSamplesBeforeRejection; i++) {
            float angle = Random::RangeFloat(0, 1) * M_PI * 2;
            Vector2f dir(std::sin(angle), std::cos(angle));

            float candidateRadius = Random::RangeFloat(minRadius, maxRadius);
            float radiusOffset = candidateRadius + spawnPoint->radius + offset;
            dir *= Random::RangeFloat(radiusOffset, radiusOffset * 2);
            Vector2i candidatePos = spawnPoint->position + Vector2i(dir);
            auto candidate = std::make_shared<PoissonPoint>(candidatePos, candidateRadius);

            if (isValid(candidate)) {
                points.push_back(candidate);
                spawnPoints.push_back(candidate);

                int gridX = int(candidate->position.x / cellSize);
                int gridY = int(candidate->position.y / cellSize);

                grid[gridX][gridY] = points.size();
                candidateAccepted = true;
                break;
            }
        }

        if (!candidateAccepted)
            spawnPoints.erase(spawnPoints.begin() + spawnIndex);
    }

    for (auto &point: points)
        point->position += center;

    return points;
}

bool PoissonDiskSampling::isValid(const std::shared_ptr<PoissonPoint> &candidate) {
    if (isInsideRegion(candidate->position, candidate->radius)) {
        int cellX = int(candidate->position.x / cellSize);
        int cellY = int(candidate->position.y / cellSize);
        int gridsToSearch = candidate->getGridsToSearch(cellSize, offset, maxRadius);

        int searchStartX = std::max(0, cellX - gridsToSearch);
        int searchStartY = std::max(0, cellY - gridsToSearch);
        int searchEndX = std::min(cellX + gridsToSearch, int(grid.size() - 1));
        int searchEndY = std::min(cellY + gridsToSearch, int(grid[0].size() - 1));

        for (int x = searchStartX; x <= searchEndX; x++) {
            for (int y = searchStartY; y <= searchEndY; y++) {
                int pointIndex = grid[x][y] - 1;

                if (pointIndex != -1) {
                    auto neighborPoint = points[pointIndex];
                    float sqrDist = (candidate->position - neighborPoint->position).sqrMagnitude();
                    float radiusOffset = candidate->radius + neighborPoint->radius + offset;

                    if (sqrDist < std::pow(radiusOffset, 2))
                        return false;
                }
            }
        }

        return true;
    }

    return false;
}

bool PoissonDiskSampling::isInsideRegion(Vector2i pointPos, float pointRadius) {
    return (pointPos.x >= pointRadius && pointPos.x < sampleRegionSize.x - 1 - pointRadius &&
            pointPos.y >= pointRadius && pointPos.y < sampleRegionSize.y - 1 - pointRadius);
}