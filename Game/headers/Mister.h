//
// Created by Ahmad Rahimi on 12/15/17.
//

#ifndef TOETS_MENEERJANSEN_H
#define TOETS_MENEERJANSEN_H


#include "MoveableObject.h"
#include "state_machine/StateMachine.h"
#include "Dog.h"
#include "DogOwner.h"

class Mister : public DogOwner {

private:
    StateMachine<Mister> *stateMachine;

public:
    Mister(int x, int y, int w, int h, int *color);

    StateMachine<Mister> *getStateMachine() const;

    void update(float time) override;

    void draw() override;
};


#endif //TOETS_MENEERJANSEN_H
