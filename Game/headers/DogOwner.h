//
// Created by Mevlüt Özdemir on 20-12-17.
//

#ifndef TOETS_DOGOWNER_H
#define TOETS_DOGOWNER_H


#include "Dog.h"

class DogOwner : public MoveableObject {

private:
    Dog *dog;

protected:
    int minWater;
    int maxWater;
    std::string name;

    double chance;
    int totalWaterGiven;
    int timesWaterGiven;

public:
    DogOwner(int x, int y, int w, int h, int *color);

    void addDog(Dog &dog);

    bool hasDog() const;

    Dog &getDog();

    int getWater(bool increaseProperties = true);

    std::string getName() const;

    void increaseTimesWaterGiven(int by = 1);

    void increaseTotalWaterGiven(int by);

    double getAverageWater() const;

    void setChance(double chance);

    double getChance() const;

    bool hasWaterGiven() const;
};


#endif //TOETS_DOGOWNER_H
