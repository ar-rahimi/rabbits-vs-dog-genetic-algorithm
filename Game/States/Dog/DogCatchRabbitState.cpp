//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <Map.h>
#include "headers/DogCatchRabbitState.h"

#include "headers/DogWanderState.h"

void DogCatchRabbitState::enterState(Dog &owner) {
    owner.generatePathToTarget();
}

void DogCatchRabbitState::exitState(Dog &owner) {

}

void DogCatchRabbitState::updateState(Dog &owner) {
    if (!owner.isFinishedPath())
        owner.followPath();
    else
        owner.getStateMachine().changeCurrentState(new DogWanderState());
}

std::string DogCatchRabbitState::getName() const {
    return "catch rabbit";
}

