//
// Created by Mevlüt Özdemir on 20-12-17.
//

#include <headers/Seconds.h>
#include "headers/DogGlobalState.h"
#include "headers/DogThirstyState.h"
#include "headers/DogCatchRabbitState.h"
#include "headers/DogGoToCaveState.h"

DogGlobalState::DogGlobalState() :
        timeToIncreaseThirst{Seconds(1).toMilliSeconds()} {
}

void DogGlobalState::enterState(Dog &owner) {

}

void DogGlobalState::exitState(Dog &owner) {

}

void DogGlobalState::updateState(Dog &owner) {
    if (owner.getTimeCounter() >= timeToIncreaseThirst) {
        owner.increaseThirst(1);
        owner.resetTimeCounter();
    }

    // just for testing
    if (Map::getMap()->rabbits.empty()) {
        owner.getStateMachine().changeCurrentState(new DogGoToCaveState());
        return;
    }

    if (owner.changePathIfRabbitNearby(15)) {
        owner.getStateMachine().changeCurrentState(new DogCatchRabbitState());
        return;
    }
}

std::string DogGlobalState::getName() const {
    return "global";
}




