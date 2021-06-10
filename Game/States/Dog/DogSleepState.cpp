//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <Map.h>
#include <RabbitGenerator.h>
#include "headers/DogSleepState.h"
#include "headers/DogGlobalState.h"
#include "headers/DogWanderState.h"

void DogSleepState::enterState(Dog &owner) {
    owner.getStateMachine().changeGlobalState(new NullState<Dog>());

}

void DogSleepState::exitState(Dog &owner) {
    owner.resetWatered();
    owner.getStateMachine().changeGlobalState(new DogGlobalState());
}

void DogSleepState::updateState(Dog &owner) {

}

std::string DogSleepState::getName() const {
    return "sleeping";
}
