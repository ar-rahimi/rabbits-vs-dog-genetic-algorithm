//
// Created by Ahmad Rahimi on 12/24/17.
//

#include <vector>
#include <Helper.h>
#include "Chromosome.h"

Chromosome::Chromosome(float affectionCohesion, float affectionAlignment, float affectionSeperation,
                       float attractionWater, float attractionDog, int fitness) :
        affectionAlignment(affectionAlignment),
        affectionCohesion(affectionCohesion),
        affectionSeperation(affectionSeperation),
        attractionDog(attractionDog),
        attractionWater(attractionWater),
        fitness(fitness)
{

}

Chromosome::Chromosome(float affectionCohesion, float affectionAlignment, float affectionSeperation,
                       float attractionWater, float attractionDog) :
        affectionAlignment(affectionAlignment),
        affectionCohesion(affectionCohesion),
        affectionSeperation(affectionSeperation),
        attractionDog(attractionDog),
        attractionWater(attractionWater)
{
    fitness = 0;
}

float Chromosome::getAffectionCohesion() const {
    return affectionCohesion;
}

float Chromosome::getAffectionAlignment() const {
    return affectionAlignment;
}

float Chromosome::getAffectionSeperation() const {
    return affectionSeperation;
}

float Chromosome::getAttractionWater() const {
    return attractionWater;
}

float Chromosome::getAttractionDog() const {
    return attractionDog;
}

float Chromosome::getFitness() const {
    return fitness;
}

Chromosome Chromosome::mergeChromosome(Chromosome c) {
    std::vector<float> chromosomeValues1 = {this->getAttractionDog(), this->getAttractionWater(), this->getAffectionAlignment(), this->getAffectionSeperation(), this->getAffectionCohesion()};
    std::vector<float> chromosomeValues2 = {c.getAttractionDog(), c.getAttractionWater(), c.getAffectionAlignment(), c.getAffectionSeperation(), c.getAffectionCohesion()};
    int splitIndex = rand() % (chromosomeValues1.size()-1) + 0;
    int mutationChance = rand() % 100 + 0;
    std::vector<float> split_left(chromosomeValues1.begin(), chromosomeValues1.begin() + splitIndex);
    std::vector<float> split_right(chromosomeValues2.begin() + splitIndex, chromosomeValues2.end());
    std::vector<float> merged = std::vector<float>();
    merged.reserve(split_left.size() + split_right.size());
    merged.insert( merged.end(), split_left.begin(), split_left.end());
    merged.insert( merged.end(), split_right.begin(), split_right.end());
    if(mutationChance == 50){
        int mutateIndex = rand() % (chromosomeValues1.size()-1) + 0;
        float mutateValue = 0;
        if(mutateIndex == 0 || mutateIndex == 1){
            mutateValue = Helper::generatRandomFloat(20);
        }else{
            mutateValue = Helper::generatRandomFloat(10);
        }
        merged[mutateIndex] = mutateValue;
        std::cout << "MUTATION! index: " + std::to_string(mutateIndex) + " changed to " + std::to_string(mutateValue) << std::endl;
    }
    return {merged.at(4),merged.at(2),merged.at(3),merged.at(1),merged.at(0)};
}

void Chromosome::setFitness(int setTo) {
    this->fitness = setTo;
}

Chromosome::Chromosome(const Chromosome &c2) {
    generation = c2.generation;
    attractionWater = c2.attractionWater;
    attractionDog = c2.attractionDog;
    affectionAlignment = c2.affectionAlignment;
    affectionSeperation = c2.affectionSeperation;
    affectionCohesion = c2.affectionCohesion;
    fitness = c2.fitness;
}

bool operator<(const Chromosome& c1,const Chromosome& c2) {
    return c1.getFitness() < c2.getFitness();
}
bool operator<=(const Chromosome& c1,const Chromosome& c2) {
    return c1.getFitness() <= c2.getFitness();
}
bool operator>(const Chromosome& c1,const Chromosome& c2) {
    return c1.getFitness() > c2.getFitness();
}
bool operator>=(const Chromosome& c1,const Chromosome& c2) {
    return c1.getFitness() >= c2.getFitness();
}
