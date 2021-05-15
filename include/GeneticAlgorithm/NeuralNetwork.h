#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "NeuronsLayer.h"

class Matrix;

class NeuralNetwork {
public:
    std::vector<int> size;
    std::vector<std::shared_ptr<NeuronsLayer>> layers;

    NeuralNetwork(const std::vector<int> &size);

    NeuralNetwork(const NeuralNetwork &nn);

    std::vector<float> predict(const Matrix &inputs);

    std::shared_ptr<NeuralNetwork> crossover(const NeuralNetwork& nn) const;

    void mutate(float mutationRate);
};