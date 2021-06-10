//
// Created by Ahmad Rahimi on 9/5/17.
//

#ifndef GLOBALS_H
#define GLOBALS_H


namespace globals {
    const int SCREEN_WIDTH = 1500;
    const int SCREEN_HEIGHT = 960;
    int MOUSEPOSITION_X = 0;
    int MOUSEPOSITION_Y = 0;
}

struct Vector2 {
    int x, y;
    Vector2() : x(0), y(0){}
    Vector2(int x, int y) : x(x), y(y){}
    Vector2 zero() {
        return Vector2(0, 0);
    }
};

#endif //SHOOTER_GLOBALS_H
