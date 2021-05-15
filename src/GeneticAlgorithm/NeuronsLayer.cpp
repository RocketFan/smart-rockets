#include "../../include/GeneticAlgorithm/NeuronsLayer.h"

#include <iostream>

NeuronsLayer::NeuronsLayer(int nInputs, int nNeurons) {
    this->weights = std::make_shared<Matrix>(nInputs, nNeurons);
    this->biases = std::make_shared<Matrix>(1, nNeurons);

    weights->randomize();
    biases->randomize();
}

NeuronsLayer::NeuronsLayer(const NeuronsLayer &layer) {
    this->weights = std::make_shared<Matrix>(*layer.weights);
    this->biases = std::make_shared<Matrix>(*layer.biases);
}

std::shared_ptr<Matrix> NeuronsLayer::forward(const Matrix &inputs) {
//    std::cout << "Inputs: " << std::endl;
//    inputs.print();
//    std::cout << "Weights: " << std::endl;
//    weights->print();
//    std::cout << "Biases: " << std::endl;
//    biases->print();

    auto sumInputs = inputs.dot(*weights)->add(*biases);
//    std::cout << "sumInputs: " << std::endl;
//    sumInputs->print();
    auto outputs = sumInputs->apply(&sigmoid);
//    std::cout << std::endl;

    return outputs;
}

float NeuronsLayer::sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}