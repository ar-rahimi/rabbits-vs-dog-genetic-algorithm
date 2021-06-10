//
// Created by Ahmad Rahimi on 12/12/17.
//

#include <headers/RenderManager.h>
#include <Map.h>
#include <Game.h>
#include <headers/Debug.h>
#include "MoveableObject.h"


MoveableObject::MoveableObject(int x, int y, int w, int h, int *color) : GameObject(x, y, w, h) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->setDestinationPoint(KmPoint(rect.getRect().x, rect.getRect().y));
}

void MoveableObject::draw() {
    SDL_SetRenderDrawColor(RenderManager::getRenderManager()->getRenderer(), color[0], color[1], color[2], 255);
    GameObject::draw();
}

void MoveableObject::update(float time) {
    this->setDestinationPoint(this->destinationPoint);
    timeCounter += time;
    float dX = destinationVector.x * speed;
    float dY = destinationVector.y * speed;
    dX = dX * time;
    dY = dY * time;
    rect.setX(rect.getX() + dX);
    rect.setY(rect.getY() + dY);
}

void MoveableObject::setDestinationPoint(const KmPoint &destinationPoint) {
    MoveableObject::destinationPoint = destinationPoint;
    this->destinationVector = KmPoint(destinationPoint.x - rect.getRect().x, destinationPoint.y - rect.getRect().y);
}

std::shared_ptr<Tile> MoveableObject::getCurrentTile() {
    if (currentTile != nullptr) {
        return currentTile;
    } else {
        return Map::getMap()->getTileAtPosition(KmPoint(this->rect.getRect().x - (rect.getRect().x % 20),
                                                        this->rect.getRect().y - (rect.getRect().y % 20)));
    }
}

void MoveableObject::popPath() {
    if (!path.empty()) {
        finishedPath = false;
        std::shared_ptr<Tile> t = path.at(0);
        path.pop_front();
        currentTile = t;
        if (Debug::DEBUG_OPTIONS_ALL || Debug::DEBUG_ASTAR_TRACE)
            t->setColor(160, 200, 0);
        setDestinationPoint(
                KmPoint(t->rect.rectTileX() + (rect.getRect().w % 20) / 2,
                        t->rect.rectTileY() + (rect.getRect().h % 20) / 2));
    } else {
        finishedPath = true;
    }
}

void MoveableObject::generatePathToTarget() {
    const SDL_Rect rect = this->rect.getRect();
    std::shared_ptr<Tile> endTile = targetTile;
    path = Map::getMap()->getAStarPath(getCurrentTile(), endTile);
    popPath();
}

void MoveableObject::followPath() {
    if (abs(this->rect.getRect().x - this->destinationPoint.x) < 10 &&
        abs(this->rect.getRect().y - this->destinationPoint.y) < 10) {
        popPath();
    }
}

bool MoveableObject::isFinishedPath() const {
    return this->finishedPath;
}

CRect MoveableObject::getRect() const {
    return this->rect;
}

void MoveableObject::setTargetTile(const std::shared_ptr<Tile> &targetTile) {
    MoveableObject::targetTile = targetTile;
}

std::shared_ptr<Tile> &MoveableObject::getTargetTile() {
    return targetTile;
}

int MoveableObject::getTimeCounter() const {
    return timeCounter;
}

void MoveableObject::resetTimeCounter() {
    timeCounter = 0;
}

FPoint MoveableObject::getPoint() {
    return FPoint(this->rect.getX(), this->rect.getY());
}

void MoveableObject::newTarget() {
    KmPoint targetPoint = Map::getMap()->getRandomGrassPoint();
    while (targetPoint.x == getRect().rectTileX() && targetPoint.y == getRect().rectTileY()) {
        targetPoint = Map::getMap()->getRandomGrassPoint();
    }
    getTargetTile() = Map::getMap()->getTileAtPosition(targetPoint);
    generatePathToTarget();
}


