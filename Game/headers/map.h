//
// Created by Ahmad Rahimi on 12/12/17.
//

#ifndef TOETS_MAP_H
#define TOETS_MAP_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "MoveableObject.h"
#include "functional"
#include "Dog.h"
#include <map>
#include <SDL_render.h>
#include <headers/RenderManager.h>
#include "Text.h"
#include "Mister.h"
#include "ForceDrivenEntity.h"
#include <queue>
#include <headers/CPriorityQueue.h>
#include <Game.h>
#include <headers/Debug.h>
#include "Missus.h"

class Map {

private:
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Tile>> grassTiles;

    std::vector<std::shared_ptr<GameObject>> waterTiles;
    std::shared_ptr<Mister> mrJansen; // todo: unique_ptr
    std::shared_ptr<Missus> msJansen; // todo: unique_ptr:
    std::shared_ptr<Tile> grot;
    void generateTile(int x, int y, Tile::TYPE type);

    void generateMoveableObject(int x, int y, char character);

    void generateEdgesForTiles();

    static Map *map;

    std::vector<Text> texts;
    SDL_Rect gameHudRect = SDL_Rect();
public:

    std::vector<std::shared_ptr<GameObject>> &getWaterTiles();
    std::shared_ptr<Dog> dog;
    Dog& getDog();

    const std::shared_ptr<Tile> &getGrot() const;

    KmPoint getRandomGrassPoint();
    KmPoint getRandomRabbitPoint();

    std::vector<std::shared_ptr<MoveableObject>> moveables;
    std::vector<std::shared_ptr<GameObject>> rabbits;
    std::vector<std::shared_ptr<GameObject>> deadrabbits;
    int maph, mapw;

    void loadMap(std::string &filePath);

    void refreshMoveables();

    void draw();

    std::shared_ptr<Tile> getTileAtPosition(KmPoint position);

    static Map *getMap();

    void drawDebug();

    void setGameHud();

    void addRabbit(std::shared_ptr<ForceDrivenEntity> rabbit);

    void removeRabbit(ForceDrivenEntity* rabbit);

    std::deque<std::shared_ptr<Tile>> getAStarPath(std::shared_ptr<Tile> startTile, std::shared_ptr<Tile> endTile);


    bool isMr(char character) const;

    bool isMs(char character) const;

    bool isDog(char character) const;

    Mister &getMrJansen() const;

    Missus &getMsJansen() const;
};


#endif //TOETS_MAP_H
