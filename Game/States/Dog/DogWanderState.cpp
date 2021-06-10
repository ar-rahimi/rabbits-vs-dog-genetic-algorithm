//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <Rabbit.h>
#include "headers/DogThirstyState.h"
#include "headers/DogWanderState.h"
#include "headers/DogCatchRabbitState.h"


void DogWanderState::enterState(Dog &owner) {

}

void DogWanderState::exitState(Dog &owner) {

}

void DogWanderState::updateState(Dog &owner) {
    if (owner.changePathIfRabbitNearby(50)) {
        owner.getStateMachine().changeCurrentState(new DogCatchRabbitState());
        return;
    }

    if (owner.needsWater()) {
        owner.getStateMachine().changeCurrentState(new DogThirstyState());
        return;
    }

    if (owner.isFinishedPath()) {
        owner.newTarget();
    } else {
        owner.followPath();
    }
}


std::string DogWanderState::getName() const {
    return "wandering";
}
