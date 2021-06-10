//
// Created by Ahmad Rahimi on 12/13/17.
//

#ifndef TOETS_SCHAAP_H
#define TOETS_SCHAAP_H

#include <deque>
#include "MoveableObject.h"
#include <iostream>
#include <memory>
#include <state_machine/StateMachine.h>
#include <vector>
#include <map>

class DogOwner;


class Dog : public MoveableObject {

private:
    int thirst;
    int maxThirst;
    int watered;
    int maxWatered;

    std::unique_ptr<StateMachine<Dog>> stateMachine;
    std::vector<DogOwner *> owners;

public:

    Dog(int x, int y, int w, int h, int *color);

    void addOwner(DogOwner &owner);

    std::vector<DogOwner *> &getOwners();

    StateMachine<Dog> &getStateMachine() const;

    void increaseThirst(int by = 1);

    void reduceThirst(int by);

    int getThirst() const;


    bool needsWater() const;

    void increaseWatered(int by = 1);

    void resetWatered();

    int getWateredTimes() const;


    bool shouldSleep() const;


    void update(float time) override;

    void draw() override;

    void equalizeOwnerChances();

    bool isWateredByAllBosses() const;

    bool isSleeping() const;

    bool changePathIfRabbitNearby(int pixels);
};


#endif //TOETS_SCHAAP_H
