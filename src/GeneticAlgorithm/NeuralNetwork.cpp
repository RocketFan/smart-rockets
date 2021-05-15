#include "../../include/GeneticAlgorithm/NeuralNetwork.h"

#include <iostream>

NeuralNetwork::NeuralNetwork(const std::vector<int> &size) {
    this->size = size;
    this->layers = std::vector<std::shared_ptr<NeuronsLayer>>(size.size() - 1);

    for (int i = 0; i < size.size() - 1; i++)
        this->layers[i] = std::make_shared<NeuronsLayer>(size[i], size[i + 1]);
};

NeuralNetwork::NeuralNetwork(const NeuralNetwork &nn) {
    this->size = nn.size;
    this->layers = std::vector<std::shared_ptr<NeuronsLayer>>(nn.layers.size());

    for (int i = 0; i < layers.size(); i++)
        this->layers[i] = std::make_shared<NeuronsLayer>(*nn.layers[i]);
}

std::vector<float> NeuralNetwork::predict(const Matrix &inputs) {
    auto output = layers[0]->forward(inputs);

    for(int i = 1; i < layers.size(); i++)
        output = layers[i]->forward(*output);

    return output->matrix;
}

std::shared_ptr<NeuralNetwork> NeuralNetwork::crossover(const NeuralNetwork &nn) const {
    auto result = std::make_shared<NeuralNetwork>(*this);

    for(int i = 0; i < result->layers.size(); i++) {
        result->layers[i]->weights->crossover(*(nn.layers[i]->weights));
        result->layers[i]->biases->crossover(*(nn.layers[i]->biases));
    }

    return result;
}

void NeuralNetwork::mutate(float mutationRate) {
    for(auto &layer : layers) {
        layer->weights->mutate(mutationRate);
        layer->biases->mutate(mutationRate);
    }
}

