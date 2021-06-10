//
// Created by Ahmad Rahimi on 12/12/17.
//

#ifndef TOETS_MOVEABLEOBJECT_H
#define TOETS_MOVEABLEOBJECT_H


#include <SDL_rect.h>
#include <headers/CRect.h>
#include <deque>
#include <headers/FPoint.h>
#include "headers/KmPoint.h"
#include "GameObject.h"

class Tile;


class MoveableObject : public GameObject {

protected:
    MoveableObject();

    std::shared_ptr<Tile> currentTile;
    int timeCounter = 0;
    float speed = 0.05;
    KmPoint destinationPoint;
    KmPoint destinationVector;
    std::shared_ptr<Tile> targetTile;
    bool finishedPath = true;
    std::deque<std::shared_ptr<Tile>> path;


public:
    void popPath();

    void generatePathToTarget();

    void followPath();

    void setTargetTile(const std::shared_ptr<Tile> &targetTile);


    MoveableObject(int x, int y, int w, int h, int color[3]);

    int color[3];

    void setDestinationPoint(const KmPoint &destinationPoint);

    void draw();

    virtual void update(float time);

    CRect getRect() const;

    std::shared_ptr<Tile> getCurrentTile();

    std::shared_ptr<Tile> &getTargetTile();

    bool isFinishedPath() const;

    int getTimeCounter() const;

    void resetTimeCounter();

    FPoint getPoint();

    void newTarget();

};


#endif //TOETS_MOVEABLEOBJECT_H
