//
// Created by Ahmad Rahimi on 9/6/17.
//

#include <math.h>
#include <cmath>
#include "Helper.h"

float Helper::degreesToRadians(double degrees) {
    return degrees / 180 * M_PI;
}

float Helper::radiansToDegrees(double radians) {
    return radians * 180 / M_PI;
}

std::string Helper::getCurrentWorkingDir(void) {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

double Helper::correctTheAngle(double angle) {
    if (angle > 90) {
        return (angle - 90);
    } else {
        return angle + 270;
    }
}

int Helper::distanceBetweenPoints(int x1, int y1, int x2, int y2) {
    return hypot(abs(x1 - x2), abs(y1 - y2));
}

int Helper::calculateAngle(int x1, int y1, int x2, int y2){
    int radians = Helper::calculateRadians(x1,y1,x2,y2);
    return radians * (180 / M_PI);
}

double Helper::calculateRadians(int x1, int y1, int x2, int y2){
    int dy = y2 - y1;
    int dx = x2 - x1;
    double radiansAngle = atan2(dy,dx);
    return radiansAngle;
}

FPoint Helper::getOppositeVector(int x1, int y1, int x2, int y2, float force) {
    double oppositeRadians = Helper::calculateRadians(x1,y1,x2,y2)-3.14;
    FPoint p = FPoint(force*cos(oppositeRadians),force*sin(oppositeRadians));
//    p.xPos += x1;
//    p.yPos += y1;
    return p;
}

float Helper::map(float x, float in_min, float in_max, float out_min, float out_max) {
    float res = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return res;
}

float Helper::generatRandomFloat(int max){
    int r = rand() % max + 0;
    return float(1.0 - float(float(r)/float(10)));
}
