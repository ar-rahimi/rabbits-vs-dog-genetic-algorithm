//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <Map.h>
#include "headers/MissusWanderState.h"
#include "headers/MissusIdleState.h"

void MissusWanderState::enterState(Missus &owner) {

}

void MissusWanderState::exitState(Missus &owner) {

}

void MissusWanderState::updateState(Missus &owner) {
    if (owner.hasNearbyRabbits(30)) {
        owner.getStateMachine()->changeCurrentState(new MissusIdleState());
        return;
    }

    if (owner.isFinishedPath()) {
        owner.newTarget();
    } else {
        owner.followPath();
    }
}

std::string MissusWanderState::getName() const {
    return "wandering";
}

