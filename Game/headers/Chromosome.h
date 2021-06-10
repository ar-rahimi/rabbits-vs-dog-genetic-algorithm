//
// Created by Ahmad Rahimi on 12/24/17.
//

#ifndef TOETS_CHROMOSOME_H
#define TOETS_CHROMOSOME_H


class Chromosome {
public:
    Chromosome() = default;
    Chromosome(float affectionCohesion, float affectionAlignment, float affectionSeperation, float attractionWater, float attractionDog, int fitness);
    Chromosome(float affectionCohesion, float affectionAlignment, float affectionSeperation, float attractionWater, float attractionDog);
    float getAffectionCohesion() const;
    float getAffectionAlignment() const;
    float getAffectionSeperation() const;
    float getAttractionWater() const;
    float getAttractionDog() const;
    float getFitness() const;
    Chromosome mergeChromosome(Chromosome c);
    int generation;

    void setFitness(int setTo);
    Chromosome(const Chromosome &c2);

private:
    float affectionCohesion;
    float affectionAlignment;
    float affectionSeperation;
    float attractionWater;
    float attractionDog;
    int fitness;
};
bool operator<(const Chromosome& c1,const Chromosome& c2);
bool operator>(const Chromosome& c1,const Chromosome& c2);
bool operator<=(const Chromosome& c1,const Chromosome& c2);
bool operator>=(const Chromosome& c1,const Chromosome& c2);

#endif //TOETS_CHROMOSOME_H
