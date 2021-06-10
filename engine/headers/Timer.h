//
// Created by Mevlüt Özdemir on 25-12-17.
//

#ifndef TOETS_TIMER_H
#define TOETS_TIMER_H


class Timer {

private:
    int fps;
    int maxFps;
    int lastUpdatedTime;

public:
    Timer(int fps, int maxFps);

    int getElapsedTime();

    void changeLastUpdateTime(int time);
};


#endif //TOETS_TIMER_H
