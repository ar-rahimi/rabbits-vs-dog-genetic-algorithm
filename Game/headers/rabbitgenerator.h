//
// Created by Ahmad Rahimi on 12/15/17.
//

#ifndef TOETS_RABBITGENERATOR_H
#define TOETS_RABBITGENERATOR_H


#include "Map.h"
#include "GeneticPopulator.h"


class RabbitGenerator {
private:
    static RabbitGenerator *rabbitGenerator;
    GeneticPopulator geneticPopulator = GeneticPopulator();
public:
    void generateNewRabbitPopulation(int size);

    static RabbitGenerator *getRabbitGenerator();

    void clearRabbits();

    void drawGenetics();


};


#endif //TOETS_RABBITGENERATOR_H
