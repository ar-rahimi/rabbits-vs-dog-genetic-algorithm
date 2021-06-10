//
// Created by Ahmad Rahimi on 12/17/17.
//

#ifndef TOETS_FPOINT_H
#define TOETS_FPOINT_H


class FPoint {
public:
    FPoint(float x, float y);
    float x;
    float y;
    FPoint operator/(const float v) const;
    FPoint operator+(const FPoint& p) const;
    FPoint operator-(const FPoint& p) const;
    void operator+=(const FPoint& p);
};


#endif //TOETS_FPOINT_H
