//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <headers/Seconds.h>
#include <Map.h>
#include "headers/MisterPictureState.h"
#include "headers/MisterWanderState.h"

MisterPictureState::MisterPictureState() :
        millisecondsTillStateFinished{Seconds(10).toMilliSeconds()} {
}

void MisterPictureState::enterState(Mister &owner) {

}

void MisterPictureState::exitState(Mister &owner) {
    owner.resetTimeCounter();
}

void MisterPictureState::updateState(Mister &owner) {
    if (isStateFinished(owner)) {
        owner.getStateMachine()->changeCurrentState(new MisterWanderState());
    }
}

std::string MisterPictureState::getName() const {
    return "taking picture";
}

bool MisterPictureState::isStateFinished(Mister &owner) const {
    return owner.getTimeCounter() >= this->millisecondsTillStateFinished;
}
