#include "../../include/GeneticAlgorithm/DNA.h"
#include "../../include/Helpers/Helpers.h"

DNA::DNA(const std::vector<int> &size) {
    this->fitness = 0;
    this->nn = std::make_shared<NeuralNetwork>(size);
}

DNA::DNA(const NeuralNetwork &nn) {
    this->fitness = 0;
    this->nn = std::make_shared<NeuralNetwork>(nn);
}

void DNA::mutate(float mutationRate) {
    nn->mutate(mutationRate);
}

void DNA::calcFitness() {
    float score = 0.01;

    score += (1 / targetDist) * 10000;

    fitness = pow(score, 4);

    if (hitTarget)
        fitness *= 1.5;
}

std::shared_ptr<DNA> DNA::crossover(const DNA &partner) {
    auto result = std::make_shared<DNA>(*nn);

    result->nn = nn->crossover(*partner.nn);

    return result;
}

std::vector<float> DNA::predict(const Matrix &inputs) {
    auto outputs = nn->predict(inputs);

    return outputs;
}