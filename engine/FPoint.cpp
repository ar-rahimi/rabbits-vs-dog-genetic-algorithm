//
// Created by Ahmad Rahimi on 12/17/17.
//

#include "headers/FPoint.h"

FPoint::FPoint(float x, float y) : x(x), y(y){

}

void FPoint::operator+=(const FPoint &p) {
    x += p.x;
    y += p.y;
}

FPoint FPoint::operator+(const FPoint &p) const {
    return FPoint(x+p.x, y+p.y);
}

FPoint FPoint::operator/(const float v) const {
    return FPoint(x / v, y / v);
}

FPoint FPoint::operator-(const FPoint &p) const {
    return FPoint(x-p.x, y-p.y);
}
