//
// Created by Mevlüt Özdemir on 20-12-17.
//

#include "headers/MissusIdleState.h"
#include "headers/MissusWanderState.h"

void MissusIdleState::enterState(Missus &owner) {

}

void MissusIdleState::exitState(Missus &owner) {

}

void MissusIdleState::updateState(Missus &owner) {
    if (!owner.hasNearbyRabbits(30)) {
        owner.getStateMachine()->changeCurrentState(new MissusWanderState());
        return;
    }
}

std::string MissusIdleState::getName() const {
    return "idle";
}
