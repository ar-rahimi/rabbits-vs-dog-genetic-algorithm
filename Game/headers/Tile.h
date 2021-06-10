//
// Created by Ahmad Rahimi on 12/12/17.
//

#ifndef TOETS_TILE_H
#define TOETS_TILE_H


#include <SDL_rect.h>
#include <string>
#include "array"
#include "map"
#include <headers/RenderManager.h>
#include <headers/CRect.h>
#include "headers/KmPoint.h"
#include "GameObject.h"

class Tile : public GameObject {
public:
    enum TYPE { WATER, GRASS, GROT};

    TYPE tiletype;

    Tile(int x, int y, int w, int h, TYPE tiletype);

    Tile() = default;

    void draw();

    void addEdge(std::shared_ptr<Tile> neighbourTile);

    const KmPoint &getWayPoint() const;

    void setColor(int r, int g, int b);

    const std::vector<std::shared_ptr<Tile>> &getEdges() const;

    struct LessThanByCost
    {
        bool operator()(const std::shared_ptr<Tile> t1, const std::shared_ptr<Tile> t2) const
        {
            return (t1->getFCost() > t2->getFCost());
        }
    };

    std::shared_ptr<Tile> parent;

    void setHCost(int hCost);

    void setGCost(int gCost);

    int getFCost() const;

    int getGCost() const;

private:
    int hCost = 0;

    int gCost = 0;

    int fCost = 0;

    KmPoint wayPoint{};

    std::vector<std::shared_ptr<Tile>> edges;

    //buur tile en de berekende vector van wayPoint(midden van deze tile) naar wayPoint van neighbour tile

    std::array<int, 3> color{};

    std::map<Tile::TYPE, std::array<int, 3>> tileColors{
            {TYPE::GRASS, std::array<int, 3> {0,255,0} },
            {TYPE::WATER, std::array<int, 3> {0,0,255} },
            {TYPE::GROT, std::array<int, 3> {128,128,128} }
    };
};


#endif //TOETS_TILE_H
