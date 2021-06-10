//
// Created by Ahmad Rahimi on 12/12/17.
//

#include <Game.h>
#include <headers/Debug.h>
#include "Tile.h"

Tile::Tile(int x, int y, int w, int h, Tile::TYPE tiletype) : GameObject(x,y,w,h), tiletype(tiletype) {
    this->color = this->tileColors.at(tiletype);
    this->wayPoint.x = this->rect.getRect().x + this->rect.getRect().w/2;
    this->wayPoint.y = this->rect.getRect().y + this->rect.getRect().h/2;
}

void Tile::draw(){
    SDL_SetRenderDrawColor(RenderManager::getRenderManager()->getRenderer(), this->color[0], this->color[1], this->color[2], 255);
//    SDL_RenderFillRect(RenderManager::getRenderManager()->getRenderer(), &this->rect.getRect());
    GameObject::draw();
    if(Debug::DEBUG_EDGE_WAYPOINTS || Debug::DEBUG_OPTIONS_ALL){
        SDL_SetRenderDrawColor(RenderManager::getRenderManager()->getRenderer(), 255, 153, 0, 255);
        SDL_RenderSetScale(RenderManager::getRenderManager()->getRenderer(), 3, 3);
        SDL_RenderDrawPoint(RenderManager::getRenderManager()->getRenderer(), this->wayPoint.x/3, this->wayPoint.y/3);
        SDL_RenderSetScale(RenderManager::getRenderManager()->getRenderer(), 1, 1);
        for (auto const& edge : edges)
        {
            SDL_RenderDrawLine(RenderManager::getRenderManager()->getRenderer(), wayPoint.x, wayPoint.y, edge->getWayPoint().x, edge->getWayPoint().y);
        }
    }
}

void Tile::addEdge(std::shared_ptr<Tile> neighbourTile){
    this->edges.emplace_back(neighbourTile);
}

const KmPoint &Tile::getWayPoint() const {
    return wayPoint;
}

void Tile::setColor(int r, int g, int b) {
    color = {r,g,b};
}

const std::vector<std::shared_ptr<Tile>> &Tile::getEdges() const {
    return edges;
}

void Tile::setHCost(int hCost) {
    Tile::hCost = hCost;
    Tile::fCost = hCost + Tile::gCost;
}

void Tile::setGCost(int gCost) {
    Tile::gCost = gCost;
    Tile::fCost = gCost + hCost;
}

int Tile::getFCost() const {
    return fCost;
}

int Tile::getGCost() const {
    return gCost;
}
