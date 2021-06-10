//
// Created by Ahmad Rahimi on 12/15/17.
//

#include <Map.h>
#include <Game.h>
#include "Mister.h"
#include "states/mister_states/headers/MisterWanderState.h"

Mister::Mister(int x, int y, int w, int h, int *color) :
        stateMachine{new StateMachine<Mister>(*this)},
        DogOwner(x, y, w, h, color) {

    stateMachine->changeCurrentState(new MisterWanderState());
    this->speed = 0.0025;
    this->minWater = 30;
    this->maxWater = 50;
    this->name = "MrJansen";
    this->chance = 50;
}

void Mister::update(float time) {
    stateMachine->update();
    MoveableObject::update(time);
}

StateMachine<Mister> *Mister::getStateMachine() const {
    return this->stateMachine;
}

void Mister::draw() {
    if (Game::DEBUGMODE) {
        RenderManager::getRenderManager()->DrawText("---" + this->name + "---", 200, 10, 100, 15, 0, 255, 0, 0);

        RenderManager::getRenderManager()->DrawText("State: " + stateMachine->getCurrentState()->getName(),
                                                    200, 25, 150, 15, 0, 255, 255, 255);

        RenderManager::getRenderManager()->DrawText(
                "Position: xPos=" + std::to_string(this->rect.getRect().x) + ", yPos=" +
                std::to_string(this->rect.getRect().y), 200, 40, 150, 15, 0, 255, 255, 255);

        RenderManager::getRenderManager()->DrawText("Timer: " + std::to_string(this->timeCounter / 1000),
                                                    200, 55, 150, 15, 0, 255, 255, 255);

        RenderManager::getRenderManager()->DrawText("Chance: %" + std::to_string(this->getChance()),
                                                    200, 70, 150, 15, 0, 255, 255, 255);
    }
    MoveableObject::draw();
}


