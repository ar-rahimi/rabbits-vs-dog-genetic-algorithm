//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_DOGTHIRSTYSTATE_H
#define TOETS_DOGTHIRSTYSTATE_H

#include "DogWanderState.h"
#include <Map.h>
#include "DogSleepState.h"
#include <Dog.h>

class DogThirstyState : public State<Dog> {

private:
    std::unique_ptr<DogOwner> boss;
    int thirstOnEnter = 0;

public:
    DogThirstyState();

    void enterState(Dog &owner) override;

    void exitState(Dog &owner) override;

    void updateState(Dog &owner) override;

    std::string getName() const override;

    bool bossFound(Dog &owner, DogOwner &boss) const;

    void goBoss(Dog &owner, DogOwner &boss);

    DogOwner &getRandomBoss(Dog &owner);

    void recalculateBossChances(Dog &owner);
};


#endif //TOETS_DOGTHIRSTYSTATE_H
