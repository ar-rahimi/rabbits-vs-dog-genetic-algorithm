//
// Created by Mevlüt Özdemir on 20-12-17.
//

#include <headers/Random.h>
#include <Map.h>
#include "DogOwner.h"

DogOwner::DogOwner(int x, int y, int w, int h, int *color) :
        totalWaterGiven{0},
        timesWaterGiven{0},
        dog{nullptr},
        MoveableObject(x, y, w, h, color) {

}


void DogOwner::addDog(Dog &dog) {
    this->dog = &dog;
    dog.addOwner(*this);
}

bool DogOwner::hasDog() const {
    return this->dog != nullptr;
}


Dog &DogOwner::getDog() {
    return *this->dog;
}

int DogOwner::getWater(bool increaseProperties) {
    int water = Random().nextInt(minWater, maxWater);

    if (increaseProperties) {
        this->increaseTotalWaterGiven(water);
        this->increaseTimesWaterGiven();
    }

    return water;
}

std::string DogOwner::getName() const {
    return this->name;
}

void DogOwner::increaseTimesWaterGiven(int by) {
    this->timesWaterGiven += by;
}

void DogOwner::increaseTotalWaterGiven(int by) {
    this->totalWaterGiven += by;
}

double DogOwner::getAverageWater() const {
    if (hasWaterGiven()) {
        return this->totalWaterGiven / this->timesWaterGiven;
    }

    return 0;
}


double DogOwner::getChance() const {
    return this->chance;
}

void DogOwner::setChance(double chance) {
    this->chance = chance;
}

bool DogOwner::hasWaterGiven() const {
    return this->timesWaterGiven > 0;
}
