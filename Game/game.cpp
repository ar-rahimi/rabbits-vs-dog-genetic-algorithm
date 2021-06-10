//
// Created by Ahmad Rahimi on 9/5/17.
//
#include <iostream>
#include <SDL.h>
#include <headers/RenderManager.h>
#include <RabbitGenerator.h>
#include <headers/Timer.h>
#include "states/dog/headers/DogWanderState.h"

namespace {
    const int FPS = 60;
    const int MAX_FPS = 120;
}

bool Game::DEBUGMODE = true;

Game::Game() :
        running{true} {
    SDL_Init(SDL_INIT_EVERYTHING);
}

void Game::start() {
    SDL_Event event{};
    RabbitGenerator rabbitGenerator;
    rabbitGenerator.generateNewRabbitPopulation(100);


    Timer timer{FPS, MAX_FPS};

    while (running) {
        SDL_PumpEvents();
        if (SDL_PollEvent(&event)) {}

        this->update(timer.getElapsedTime());
        this->draw();
    }
}

void Game::draw() {
    RenderManager::getRenderManager()->clear();
    Map::getMap()->draw();
    RabbitGenerator::getRabbitGenerator()->drawGenetics();
    RenderManager::getRenderManager()->flip();
}

void Game::update(float elapsedTime) {
    Map::getMap()->refreshMoveables();
    shouldGenerateNewPopulation();

    for (const auto &moveable : Map::getMap()->moveables) {
        moveable->update(elapsedTime);
    }
}

void Game::shouldGenerateNewPopulation() {
    auto &dog = Map::getMap()->getDog();

    if (dog.isSleeping()) {
        RabbitGenerator::getRabbitGenerator()->generateNewRabbitPopulation(100);
        dog.getStateMachine().changeCurrentState(new DogWanderState());
    }
}

Game::~Game() = default;
