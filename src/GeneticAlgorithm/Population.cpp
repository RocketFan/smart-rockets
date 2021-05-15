#include "../../include/GeneticAlgorithm/Population.h"

#include "../../include/GameObjects/Rocket.h"

Population::Population(const std::vector<int> &size, float mutationRate, int popNumber) {
    this->mutationRate = mutationRate;
    this->popNumber = popNumber;
    this->generations = 0;
    this->population.reserve(popNumber);
    this->probs.reserve(popNumber);

    for(int i = 0; i < probs.capacity(); i++) {
        population.push_back(std::make_shared<DNA>(size));
        probs.push_back(0);
    }
}

void Population::setDNAToRockets(std::vector<std::shared_ptr<class Rocket>> &rockets) {
    for(int i = 0; i < rockets.size(); i++)
        rockets[i]->setDNA(population[i].get());
}

void Population::naturalSelection() {
    float sumProbs = 0;

    best = nullptr;

    for (int i = 0; i < population.size(); i++) {
        auto dna = population[i];

        dna->calcFitness();
        probs[i] = dna->fitness;
        sumProbs += dna->fitness;

        if (dna || dna->fitness >= best->fitness)
            best = dna;
    }

    for (auto &prob : probs)
        prob /= sumProbs;
}

void Population::generate() {
    std::vector<std::shared_ptr<DNA>> popCopy(population);

    for (auto &dna : population) {
        int indexA = getPopIndex();
        int indexB = getPopIndex();

        auto partnerA = popCopy[indexA];
        auto partnerB = popCopy[indexB];

        auto child = partnerA->crossover(*partnerB);
        child->mutate(mutationRate);
        dna = child;
    }

    generations += 1;
}

float Population::getAvgFitness() {
    float total = 0;

    for (auto &dna : population)
        total += dna->fitness;

    return total / popNumber;
}

int Population::getPopIndex() {
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    int index = 0;

    while(r >= 0 && index < probs.size()){
        r -= probs[index];
        index++;
    }

    return index - 1;
}