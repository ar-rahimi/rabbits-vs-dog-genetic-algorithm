//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_MISSUS_H
#define TOETS_MISSUS_H


#include "Dog.h"
#include "DogOwner.h"

class Missus : public DogOwner {

private:
    StateMachine<Missus> *stateMachine;

public:
    Missus(int x, int y, int w, int h, int *color);

    StateMachine<Missus> *getStateMachine() const;

    void update(float time) override;

    void draw() override;

    bool hasNearbyRabbits(int pixels);
};


#endif //TOETS_MISSUS_H
