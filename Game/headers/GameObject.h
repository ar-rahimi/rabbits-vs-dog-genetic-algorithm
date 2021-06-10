//
// Created by Ahmad Rahimi on 12/17/17.
//

#ifndef TOETS_GAMEOBJECT_H
#define TOETS_GAMEOBJECT_H


#include <headers/CRect.h>
#include <vector>

class GameObject {

private:
protected:

    bool visible = true;

public:
    int x, y;
    static int index;
    int id;

    GameObject(int x = 0, int y = 0, int w = 0, int h = 0);

    CRect rect{};

    virtual void draw();

    bool isVisible() const;
};


#endif //TOETS_GAMEOBJECT_H
