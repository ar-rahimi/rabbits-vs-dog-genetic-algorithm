//
// Created by Ahmad Rahimi on 12/24/17.
//

#ifndef TOETS_GENETICPOPULATOR_H
#define TOETS_GENETICPOPULATOR_H


#include <vector>
#include "Rabbit.h"

class GeneticPopulator {
    std::vector<Chromosome> chromosomes;
    std::vector<Chromosome> sortedChromosome;
    float totalSum = 0;
    Chromosome curBestChromosome;
    Chromosome curBaddestChromosome;
    float curAvgChromosome;

    Chromosome bestChromosome;
    Chromosome baddestChromosome;
    float avgChromosome;

    int generation = 0;
    int generateCount = 0;
    int maxGenerate = 100;
public:
    int getGeneration() const;
    GeneticPopulator();
    void insertToPopulation(Chromosome chromosome);
    Chromosome getChromosome();

    void clearChromosomes();
    void updateChromosomeBoard(Chromosome chromosome);
    void increaseGeneration();
    std::shared_ptr<Rabbit> generateRabbitFromParents(KmPoint generationPoint);
    void prepareChromosomes();
    void drawDebug();
};


#endif //TOETS_GENETICPOPULATOR_H
