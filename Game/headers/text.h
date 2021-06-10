//
// Created by Ahmad Rahimi on 12/14/17.
//

#ifndef TOETS_TEXT_H
#define TOETS_TEXT_H


#include <headers/KmPoint.h>
#include <string>
#include <headers/RenderManager.h>
#include <headers/CRect.h>

class Text {

public:
    Text(CRect bounds, std::string text, int r, int g, int b, int angle);
    CRect bounds;
    std::string text;
    int r;
    int g;
    int b;
    int angle;
    void draw();
};


#endif //TOETS_TEXT_H
