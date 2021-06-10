//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <Map.h>
#include <headers/Seconds.h>
#include "headers/MisterWanderState.h"
#include "headers/MisterPictureState.h"

MisterWanderState::MisterWanderState() :
        millisecondsTillPictureState{Seconds(20).toMilliSeconds()} {
}


void MisterWanderState::enterState(Mister &owner) {

}

void MisterWanderState::exitState(Mister &owner) {
    owner.resetTimeCounter();
}

void MisterWanderState::updateState(Mister &owner) {
    if (this->isTimeForPictureState(owner)) {
        owner.getStateMachine()->changeCurrentState(new MisterPictureState());
    }

    if (owner.isFinishedPath()) {
        owner.newTarget();
    } else {
        owner.followPath();
    }
}

std::string MisterWanderState::getName() const {
    return "wandering";
}

bool MisterWanderState::isTimeForPictureState(Mister &owner) const {
    return owner.getTimeCounter() >= millisecondsTillPictureState;
}
