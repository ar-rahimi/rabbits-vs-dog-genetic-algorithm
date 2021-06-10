//
// Created by Mevlüt Özdemir on 30-10-17.
//

#include <random>
#include "headers/Random.h"


int Random::nextInt(int min, int max) const {
    return getRandom(min, max);
}

int Random::nextInt(int max) const {
    return getRandom(0, max);
}

int Random::getRandom(int min, int max) const {
    std::default_random_engine generator;
    generator.seed(time(0));

    std::uniform_int_distribution<int> distribution2(min, max);
    return distribution2(generator);
}