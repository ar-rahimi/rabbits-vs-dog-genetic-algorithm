//
// Created by Ahmad Rahimi on 9/5/17.
//

#ifndef GAME_H
#define GAME_H

#include <Map.h>

class RenderManager;

class Game {

private:
    bool running;

    void draw();

    void update(float elapsedTime);

public:
    Game();

    static bool DEBUGMODE;

    void start();

    ~Game();

    void shouldGenerateNewPopulation();
};

#endif //SHOOTER_GAME_H
