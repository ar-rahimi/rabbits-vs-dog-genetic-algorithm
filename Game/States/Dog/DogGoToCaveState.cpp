//
// Created by Mevlüt Özdemir on 25-12-17.
//

#include <Map.h>
#include "headers/DogGoToCaveState.h"
#include "headers/DogSleepState.h"

void DogGoToCaveState::enterState(Dog &owner) {
    owner.setTargetTile(Map::getMap()->getGrot());
    owner.generatePathToTarget();
    owner.getStateMachine().changeGlobalState(new NullState<Dog>());
}

void DogGoToCaveState::exitState(Dog &owner) {

}

void DogGoToCaveState::updateState(Dog &owner) {
    if (!owner.isFinishedPath()) {
        owner.followPath();
    } else {
        owner.getStateMachine().changeCurrentState(new DogSleepState());
    }
}

std::string DogGoToCaveState::getName() const {
    return "go to cave";
}
