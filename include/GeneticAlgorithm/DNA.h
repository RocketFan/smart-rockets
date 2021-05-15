#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <cmath>

#include "NeuralNetwork.h"
#include "../Helpers/Vector2.h"

class DNA {
public:
    std::shared_ptr<NeuralNetwork> nn;
    Vector2f targetDir;
    float targetDist;
    bool hitTarget;
    float fitness;

    DNA(const std::vector<int> &size);

    DNA(const NeuralNetwork &nn);

    void mutate(float mutationRate);

    void calcFitness();

    std::shared_ptr<DNA> crossover(const DNA &partner);

    std::vector<float> predict(const Matrix &inputs);
};