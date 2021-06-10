//
// Created by Mevlüt Özdemir on 25-12-17.
//

#include <SDL_timer.h>
#include <algorithm>
#include "headers/Timer.h"

Timer::Timer(int fps, int maxFps) :
        fps{fps},
        maxFps{maxFps},
        lastUpdatedTime{SDL_GetTicks()} {

}

int Timer::getElapsedTime() {
    int currentTimeMs = SDL_GetTicks();
    int elapsedTimeMs = currentTimeMs - lastUpdatedTime;
    changeLastUpdateTime(currentTimeMs);

    return std::min(elapsedTimeMs, maxFps);
}

void Timer::changeLastUpdateTime(int time) {
    lastUpdatedTime = time;
}


