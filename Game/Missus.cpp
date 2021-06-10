//
// Created by Mevlüt Özdemir on 18-12-17.
//

#include <Game.h>
#include "Missus.h"
#include "states/missus_states/headers/MissusWanderState.h"

Missus::Missus(int x, int y, int w, int h, int *color) :
        stateMachine{new StateMachine<Missus>(*this)},
        DogOwner(x, y, w, h, color) {
    stateMachine->changeCurrentState(new MissusWanderState());
    this->speed = 0.0025;
    this->minWater = 10;
    this->maxWater = 80;
    this->name = "MsJansen";
    this->chance = 50;
}

void Missus::update(float time) {
    stateMachine->update();
    MoveableObject::update(time);
}

StateMachine<Missus> *Missus::getStateMachine() const {
    return this->stateMachine;
}


void Missus::draw() {
    if (Game::DEBUGMODE) {
        RenderManager::getRenderManager()->DrawText("---" + this->name + "---", 400, 10, 100, 15, 0, 255, 0, 0);

        RenderManager::getRenderManager()->DrawText("State: " + stateMachine->getCurrentState()->getName(),
                                                    400, 25, 150, 15, 0, 255, 255, 255);

        RenderManager::getRenderManager()->DrawText(
                "Position: xPos=" + std::to_string(this->rect.getRect().x) + ", yPos=" +
                std::to_string(this->rect.getRect().y), 400, 40, 150, 15, 0, 255, 255, 255);

        RenderManager::getRenderManager()->DrawText("Timer: " + std::to_string(this->timeCounter / 1000),
                                                    400, 55, 150, 15, 0, 255, 255, 255);

        RenderManager::getRenderManager()->DrawText("Chance: %" + std::to_string(this->getChance()),
                                                    400, 70, 150, 15, 0, 255, 255, 255);
    }
    MoveableObject::draw();
}

bool Missus::hasNearbyRabbits(int pixels) {
    for (auto &rabbit : Map::getMap()->rabbits) {
        if (Helper::distanceBetweenPoints(rabbit->rect.getOriginX(), rabbit->rect.getOriginY(),
                                          this->rect.getOriginX(), this->rect.getOriginY()) <= pixels) {
            return true;
        }
    }
    return false;
}
