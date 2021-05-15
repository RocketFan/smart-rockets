#pragma once

#include <memory>
#include <cmath>

#include "../Helpers/Matrix.h"

class NeuronsLayer {
public:
    std::shared_ptr<Matrix> weights;
    std::shared_ptr<Matrix> biases;

    NeuronsLayer(int nInputs, int nNeurons);

    NeuronsLayer(const NeuronsLayer &layer);

    std::shared_ptr<Matrix> forward(const Matrix &inputs);

    static float sigmoid(float x);
};