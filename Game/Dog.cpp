//
// Created by Ahmad Rahimi on 12/13/17.
//

#include <Map.h>
#include <queue>
#include <Game.h>
#include "Dog.h"
#include "States/Dog/headers/DogWanderState.h"
#include "States/Dog/headers/DogGlobalState.h"
#include "Rabbit.h"

Dog::Dog(int x, int y, int w, int h, int *color) :
        thirst{0},
        maxThirst{100},
        watered{0},
        maxWatered{2},
        stateMachine{std::make_unique<StateMachine<Dog>>(*this)},
        MoveableObject(x + w / 2, y + h / 2, w, h, color) {

    stateMachine->changeGlobalState(new DogGlobalState());
    stateMachine->changeCurrentState(new DogWanderState());

    this->speed = 0.005;
    targetTile = getCurrentTile();
}

void Dog::addOwner(DogOwner &owner) {
    this->owners.emplace_back(&owner);
    this->equalizeOwnerChances();
}

void Dog::equalizeOwnerChances() {
    auto totalOwners = static_cast<int>(owners.size());
    double chancePerOwner = 100 / totalOwners;

    for (auto &owner : owners) {
        owner->setChance(chancePerOwner);
    }
}

std::vector<DogOwner *> &Dog::getOwners() {
    return this->owners;
}


void Dog::update(float time) {
    stateMachine->update();
    MoveableObject::update(time);
}

void Dog::increaseThirst(int by) { // default = 1
    this->thirst += by;
    if (this->thirst > maxThirst)
        this->thirst = maxThirst;
}

void Dog::reduceThirst(int by) {
    this->thirst -= by;
    if (this->thirst < 0)
        this->thirst = 0;
}

int Dog::getThirst() const {
    return this->thirst;
}

bool Dog::needsWater() const {
    return this->thirst >= this->maxThirst;
}

void Dog::increaseWatered(int by) { // default = 1
    this->watered += by;
    if (watered > maxWatered)
        this->watered = maxWatered;
}

void Dog::resetWatered() {
    this->watered = 0;
}

int Dog::getWateredTimes() const {
    return this->watered;
}

bool Dog::shouldSleep() const {
    return this->watered >= maxWatered;
}

StateMachine<Dog> &Dog::getStateMachine() const {
    return *stateMachine;
}

bool Dog::isWateredByAllBosses() const {
    for (auto &boss : owners) {
        if (!boss->hasWaterGiven()) {
            return false;
        }
    }
    return true;
}


bool Dog::isSleeping() const {
    return this->stateMachine->getCurrentState()->getName() == "sleeping";
}


bool Dog::changePathIfRabbitNearby(int pixels)  {
    for (auto &rabbit : Map::getMap()->rabbits) {
        if (Helper::distanceBetweenPoints(rabbit->rect.getOriginX(), rabbit->rect.getOriginY(),
                                          this->rect.getOriginX(), this->rect.getOriginY()) <= pixels) {
            setTargetTile(Map::getMap()->getTileAtPosition(KmPoint(rabbit->rect.getX(), rabbit->rect.getY())));
            auto *temp = dynamic_cast<Rabbit*>(rabbit.get());
            temp->increaseChase();
            return true;
        }
    }
    return false;
}


void Dog::draw() {
    if (Game::DEBUGMODE) {
        RenderManager::getRenderManager()->DrawText("---dog---", 10, 10, 100, 15, 0, 255, 0, 0);
        RenderManager::getRenderManager()->DrawText("State: " + this->stateMachine->getCurrentState()->getName(), 10,
                                                    25, 150, 15, 0, 255, 255,
                                                    255);
        RenderManager::getRenderManager()->DrawText("Thirst: " + std::to_string(thirst), 10, 40, 150, 15, 0, 255, 255,
                                                    255);
        RenderManager::getRenderManager()->DrawText(
                "Position: xPos=" + std::to_string(this->rect.getRect().x) + ", yPos=" +
                std::to_string(this->rect.getRect().y), 10, 55, 150, 15, 0, 255,
                255, 255);
        RenderManager::getRenderManager()->DrawText("Timer: " + std::to_string(this->timeCounter / 1000), 10, 70, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Watered: " + std::to_string(this->watered), 10, 85, 150,
                                                    15, 0, 255, 255, 255);
    }
    MoveableObject::draw();
}









