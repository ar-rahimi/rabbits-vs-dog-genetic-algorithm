//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_DOGWANDERSTATE_H
#define TOETS_DOGWANDERSTATE_H


#include <iostream>
#include <Map.h>
#include "state_machine/State.h"
#include <Dog.h>

class DogWanderState : public State<Dog> {

public:
    void enterState(Dog &owner) override;

    void exitState(Dog &owner) override;

    void updateState(Dog &owner) override;

    std::string getName() const override;

    bool hasRabbitsWithin(Dog &owner, int pixels) const;
};


#endif //TOETS_DOGWANDERSTATE_H
