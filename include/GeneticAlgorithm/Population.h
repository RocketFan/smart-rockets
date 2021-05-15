#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "DNA.h"

class Rocket;

class Population {
public:
    int popNumber;
    int generations;
    float mutationRate;
    std::shared_ptr<DNA> best;
    std::vector<std::shared_ptr<DNA>> population;

    Population(const std::vector<int> &size, float mutationRate, int popNumber);

    void render(sf::RenderTarget &target);

    void setDNAToRockets(std::vector<std::shared_ptr<class Rocket>> &rockets);

    void naturalSelection();

    void generate();

    float getAvgFitness();

private:
    std::vector<float> probs;

    int getPopIndex();
};