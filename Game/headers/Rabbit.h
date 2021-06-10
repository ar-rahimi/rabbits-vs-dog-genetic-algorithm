//
// Created by Ahmad Rahimi on 12/23/17.
//

#ifndef TOETS_RABBIT_H
#define TOETS_RABBIT_H

#include "ForceDrivenEntity.h"
#include "Chromosome.h"
#include <Map.h>

class Rabbit : public ForceDrivenEntity {
private:
    std::map<std::string, float> attractedToSheep;
    std::map<std::string, float> attractedToWater;
    std::map<std::string, float> affectedCohesion;
    std::map<std::string, float> affectedSeperation;
    std::map<std::string, float> affectedAlignment;
    float timeSurvived = 0;
    int chased = 0;
    int seperatedFromDogCount = 0;

public:
    Rabbit(int x, int y, int w, int h, int *color, Chromosome chromosome);
    void calcAndApplyForces() override;

    void setVariables(float attractedToSheep, float attractedToWater, float affectedCohesion, float affectedSeperation, float affectedAlignment);

    //cohesion affection
    void coheseToRabbits();
    void setCohesionToRabbits(float cohesionForce);

    //water affection
    void alignWithRabbits();
    void setAlignmentWithRabbits(float alignment);

    //seperation affection
    void seperateFromRabbits();
    void setSeperationFromRabbits(float seperationForce);

    //sheep affection
    void attractToSheep();
    void setAttractedToSheep(float attraction);

    //water affection
    void attractToWater();
    void setAttractedToWater(float attraction);

    //fitness
    void update(float time);
    void updateFitness(float updateBy);
    int getFitness();

    void shouldDie();

    void increaseChase();

    Chromosome getChromosome();
};


#endif //TOETS_RABBIT_H
