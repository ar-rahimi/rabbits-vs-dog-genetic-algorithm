//
// Created by Ahmad Rahimi on 12/13/17.
//

#ifndef TOETS_POINT_H
#define TOETS_POINT_H


class KmPoint {
public:
    KmPoint(int x,int y);
    KmPoint() = default;
    int x;
    int y;
    friend bool operator<(const KmPoint& p1, const KmPoint& p2);
    KmPoint operator/(const float v) const;
    KmPoint operator+(const KmPoint& p) const;
    void operator+=(const KmPoint& p);
};


#endif //TOETS_POINT_H
