//
// Created by Ahmad Rahimi on 9/6/17.
//

#ifndef HELPER_H
#define HELPER_H
#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>
#include <headers/KmPoint.h>
#include <headers/FPoint.h>

class Helper {
public:
    static float radiansToDegrees(double radians);
    static float degreesToRadians(double degrees);
    static std::string getCurrentWorkingDir();
    static double correctTheAngle(double angle);
    static int distanceBetweenPoints(int x1, int y1, int x2, int y2);
    static FPoint getOppositeVector(int x1, int y1, int x2, int y2, float force);
    static int calculateAngle(int x1, int y1, int x2, int y2);
    static double calculateRadians(int x1, int y1, int x2, int y2);
    static float map(float x, float in_min, float in_max, float out_min, float out_max);
    static float generatRandomFloat(int max);
};

#endif //SHOOTER_HELPER_H
