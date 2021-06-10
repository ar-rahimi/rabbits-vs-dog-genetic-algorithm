//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <headers/Random.h>
#include "headers/DogThirstyState.h"
#include "headers/DogGoToCaveState.h"

DogThirstyState::DogThirstyState() :
        boss{nullptr} {
}


void DogThirstyState::enterState(Dog &owner) {
    thirstOnEnter = owner.getThirst();
    boss.reset(&getRandomBoss(owner));
}

void DogThirstyState::exitState(Dog &owner) {
}


void DogThirstyState::updateState(Dog &owner) {
    owner.setTargetTile(boss->getCurrentTile());
    owner.generatePathToTarget();

    this->goBoss(owner, *boss);

    if (this->bossFound(owner, *boss)) {
        int water = boss->getWater(true);
        owner.reduceThirst(water);
        owner.increaseWatered();
        this->recalculateBossChances(owner);

        owner.getStateMachine().changeCurrentState(new DogWanderState());
    }

    if (owner.shouldSleep()) {
        owner.getStateMachine().changeCurrentState(new DogGoToCaveState());
        return;
    }

}

DogOwner &DogThirstyState::getRandomBoss(Dog &owner) {
    double percentage = Random().nextInt(100);
    double chanceOfPreviousBoss = 0.0;

    for (auto &boss : owner.getOwners()) {
        double percentageRange = boss->getChance() + chanceOfPreviousBoss;

        if (percentage > percentageRange) {
            chanceOfPreviousBoss += boss->getChance();
            continue;
        }

        return *boss;
    }

    return *owner.getOwners()[0];
}

void DogThirstyState::recalculateBossChances(Dog &owner) {

    if (!owner.isWateredByAllBosses()) {
        // if not all bosses have given water to the dog.
        // we don't want yet to change the chances
        // of the owners, so we return for now.
        return;
    }

    double totalAverageWater{};

    for (auto &boss : owner.getOwners()) {
        totalAverageWater += boss->getAverageWater();
    }

    for (auto &boss : owner.getOwners()) {
        // calculate the chance for the owner
        // based on his average given water.
        double chance = (boss->getAverageWater() * 100) / totalAverageWater;
        boss->setChance(chance);
    }
}


void DogThirstyState::goBoss(Dog &owner, DogOwner &boss) {
    if (!bossFound(owner, boss)) {
        owner.followPath();
    }
}

bool DogThirstyState::bossFound(Dog &owner, DogOwner &boss) const {
    return owner.getCurrentTile().get() == boss.getCurrentTile().get();
}

std::string DogThirstyState::getName() const {
    return "thirsty";
}









