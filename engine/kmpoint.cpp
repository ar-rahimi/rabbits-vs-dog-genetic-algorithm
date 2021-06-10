//
// Created by Ahmad Rahimi on 12/13/17.
//

#include "headers/KmPoint.h"

KmPoint::KmPoint(int x, int y) : x(x), y(y){

}

bool operator<(const KmPoint &p1, const KmPoint &p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

KmPoint KmPoint::operator/(const float v) const
{
    return KmPoint(x / v, y / v);
}

KmPoint KmPoint::operator+(const KmPoint &p) const {
    return KmPoint(x+p.x, y+p.y);
}

void KmPoint::operator+=(const KmPoint &p) {
    x+=p.x;
    y+=p.y;
}