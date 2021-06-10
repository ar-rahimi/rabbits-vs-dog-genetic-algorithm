//
// Created by Ahmad Rahimi on 12/12/17.
//


#include "Map.h"
#include "Rabbit.h"


Map *Map::map;

void Map::loadMap(std::string &filePath) {
    std::string line;
    std::ifstream myfile("content/graaf.txt");

    std::map<char, Tile::TYPE> stringtotiletype = {{'~', Tile::WATER},
                                                   {'X', Tile::GRASS},
                                                   {'O', Tile::GROT},
                                                   {'M', Tile::GRASS},
                                                   {'V', Tile::GRASS}};

    if (myfile.is_open()) {
        int x = 0;
        int y = 0;

        while (getline(myfile, line)) {
            x = 0;
            for (auto &character : line) {
                if (stringtotiletype.count(character)) {
                    int width = x * 20;
                    int height = y * 20;
                    generateTile(width, height, stringtotiletype.at(character));
                    generateMoveableObject(width, height, character);

                    x++;
                }
            }
            y++;
        }

        mapw = x * 20 + 20;
        maph = y * 20 + 20;
        myfile.close();
    }


    mrJansen->addDog(*dog);
    msJansen->addDog(*dog);


    generateEdgesForTiles();
    setGameHud();
}

void Map::generateTile(int x, int y, Tile::TYPE type) {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(x, y, 20, 20, type);


    if (type != Tile::WATER) {
        this->grassTiles.emplace_back(tile);
        if (type == Tile::GROT)
            this->grot = tile;
    }

    if (type == Tile::WATER)
        this->waterTiles.emplace_back(tile);

    if (type == Tile::GRASS)
        this->grassTiles.emplace_back(tile);

    this->tiles.emplace_back(tile);
}

void Map::draw() {
    for (const auto &tile : tiles) {
        tile->draw();
    }

    if (Game::DEBUGMODE)
        this->drawDebug();

    for (auto &moveable : moveables) {
        moveable->draw();
    }

    for (auto &text : texts) {
        text.draw();
    }

    SDL_SetRenderDrawColor(RenderManager::getRenderManager()->getRenderer(), 0, 0, 0, 255);
}

void Map::generateMoveableObject(int x, int y, char character) {
    if (isDog(character)) {
        int rgb[3] = {150, 75, 0};
        this->dog = std::make_shared<Dog>(x, y, 10, 10, rgb);
        this->moveables.emplace_back(dog);
    }

    if (isMr(character)) {
        int rgb[3] = {255, 0, 10};
        mrJansen = std::make_shared<Mister>(x, y, 20, 20, rgb);
        this->moveables.emplace_back(mrJansen);
    }

    if (isMs(character)) {
        int rgb[3] = {255, 0, 255};
        msJansen = std::make_shared<Missus>(x, y, 20, 20, rgb);
        this->moveables.emplace_back(msJansen);
    }

}

bool Map::isMr(char character) const {
    return character == 'M';
}

bool Map::isMs(char character) const {
    return character == 'V';
}

bool Map::isDog(char character) const {
    return character == 'O';
}

void Map::generateEdgesForTiles() {
    for (auto &tile : tiles) {

        if (tile->tiletype == Tile::WATER) {
            continue;
        }

        int x = tile->rect.getRect().x / tile->rect.getRect().w;
        int y = tile->rect.getRect().y / tile->rect.getRect().h;

        for (auto &other : tiles) {
            if (other->tiletype != Tile::WATER) {
                int nX = other->rect.getRect().x / other->rect.getRect().w;
                int nY = other->rect.getRect().y / other->rect.getRect().h;
                if (x != nX || y != nY) {
                    int xRes = x - nX; //-1 == left +1 == right 0 == same xPos
                    int yRes = y - nY; //-1 == down +1 == up 0 == same yPos

                    if (xRes == 1 && yRes == 0) {
                        tile->addEdge(other);
                    } else if (xRes == 0 && yRes == 1) {
                        tile->addEdge(other);
                    }
                    if (xRes == -1 && yRes == 0) {
                        tile->addEdge(other);
                    } else if (xRes == 0 && yRes == -1) {
                        tile->addEdge(other);
                    }
                }
            }
        }

    }
}

Map *Map::getMap() {
    if (!map) {
        map = new Map();
        std::string filepath = "content/graaf.txt";
        map->loadMap(filepath);
    }
    return map;
}

std::shared_ptr<Tile> Map::getTileAtPosition(KmPoint
                                             position) {

    position.
            x = ((position.x - position.x % 20) / 20);
    position.
            y = ((position.y - position.y % 20) / 20);

    int vectorPosH = position.x;
    int vectorPosV = (position.y * (((this->mapw - 20) / 20)));
//this->tiles.at(vectorPosV+vectorPosH).get()->setColor(colors.at(0), colors.at(1), colors.at(2));
    return this->tiles.at(vectorPosV + vectorPosH);
}

KmPoint Map::getRandomGrassPoint() {
    int randIndex = static_cast<int>(rand() % (grassTiles.size() - 1) + 0);
    CRect rect = grassTiles.at(randIndex)->rect;
    return KmPoint(rect.getX(), rect.getY());
}


std::deque<std::shared_ptr<Tile>> Map::getAStarPath(std::shared_ptr<Tile> startTile, std::shared_ptr<Tile> endTile) {

    if (Debug::DEBUG_OPTIONS_ALL || Debug::DEBUG_ASTAR_COLORING || Debug::DEBUG_ASTAR_ENDTILE ||
        Debug::DEBUG_ASTAR_TRACE) {
        for (auto tile : grassTiles) {
            if (tile->tiletype == Tile::GRASS)
                tile->setColor(0, 255, 0);
            if (tile->tiletype == Tile::GROT)
                tile->setColor(128, 128, 128);
        }
        if (Debug::DEBUG_OPTIONS_ALL || Debug::DEBUG_ASTAR_ENDTILE) {
            endTile->setColor(0, 0, 0);
        }
    }
    CPriorityQueue<std::shared_ptr<Tile>, std::vector<std::shared_ptr<Tile>>, Tile::LessThanByCost> open;
    std::vector<std::shared_ptr<Tile>> closed;
    std::vector<std::shared_ptr<Tile>> allTiles;
    std::deque<std::shared_ptr<Tile>> path;
    startTile->setHCost(0); //hcost heuristic
    startTile->setGCost(0); //gcost is van begin punt tot en met huidige node
    closed.emplace_back(startTile);
    SDL_Rect endRect = endTile->rect.getRect();

    int movementCost = 1;

    bool foundEndTile = false;
    allTiles.push_back(startTile);
    allTiles.push_back(endTile);
    while (!foundEndTile) {
        //gebruik de laatst toegevoegde node
        std::shared_ptr<Tile> currentTile = closed.at(closed.size() - 1);
        for (auto &edge : currentTile->getEdges()) {
            //voeg tile toe aan alltiles om deze parents later weer te legen!
            allTiles.push_back(edge);
            //check of je het eind hebt gehaald zoja eindig de zoektocht!
            if (edge.get() == endTile.get()) {
                edge->parent = currentTile;
                foundEndTile = true;
                break;
            }
            //check of deze edge niet in de closed list zit
            if (std::find(closed.begin(), closed.end(), edge) == closed.end()) {
                //check of deze edge in open list zit
                if (open.exists(edge)) {
                    //check of de huidige gCost lager is dan als je het via deze node berekent
                    if ((currentTile->getGCost() + movementCost) < edge->getGCost()) {
                        //als het lager is verander de gcost en zet de nieuwe parent naar de huidige tile
                        edge->setGCost(currentTile->getGCost() + movementCost);
                        edge->parent = currentTile;
                    }
                } else {
                    //geef de edge de parent als currentTile, bereken de heuristic en ze de gCost en hCost, vervolgens sla het op in de open list
                    edge->parent = currentTile;
                    int distToTarget =
                            hypot(abs(edge->rect.getRect().x - endRect.x), abs(edge->rect.getRect().y - endRect.y));
                    edge->setGCost(currentTile->getGCost() + movementCost);
                    edge->setHCost(distToTarget / 20);
                    open.push(edge);
                }
            }
        }
        //check of de targettile al in de closed list zit
        if (std::find(closed.begin(), closed.end(), endTile) != closed.end() || open.empty()) {
            foundEndTile = true;
        } else {
            //pak de laagste movement cost( hcost + gcost) van de open en pop deze van de open
            std::shared_ptr<Tile> bestTile = open.top();
            //std::shared_ptr<Tile> lastTile = closed.at(closed.size() - 1);
            if (Debug::DEBUG_ASTAR_COLORING || Debug::DEBUG_OPTIONS_ALL) {
                bestTile->setColor(255, 255, 255);
            }
            open.pop();
            closed.emplace_back(bestTile);
        }
    }
    //volg de pad vanaf de endtile terug naar de currenttile via de parents en zet return deze als een dequeue
    std::shared_ptr<Tile> tile = endTile;
    while (tile != nullptr) {
        path.emplace_front(tile);
        tile = tile->parent;
    }
    //leeg alle parents vervolgens, voor de volgende keer alvast
    for (auto tile : allTiles) {
        tile->parent = nullptr;
    }
    return path;
}

void Map::drawDebug() {

    if (Debug::DEBUG_HUD || Debug::DEBUG_OPTIONS_ALL) {
        SDL_SetRenderDrawBlendMode(RenderManager::getRenderManager()->getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(RenderManager::getRenderManager()->getRenderer(), 0, 0, 0, 150);
        SDL_RenderFillRect(RenderManager::getRenderManager()->getRenderer(), &this->gameHudRect);
    }

    RenderManager::getRenderManager()->DrawText("---Map---", 600, 10, 150,
                                                15, 0, 255, 0, 0);
    if (Debug::DEBUG_OPTIONS_RABBITINFO || Debug::DEBUG_OPTIONS_ALL) {
        RenderManager::getRenderManager()->DrawText("Rabbits: " + std::to_string(this->rabbits.size()), 600, 25, 150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Moveables: " + std::to_string(this->moveables.size()), 600, 40,
                                                    150,
                                                    15, 0, 255, 255, 255);
        RenderManager::getRenderManager()->DrawText("Dead: " + std::to_string(this->deadrabbits.size()), 600, 55, 150,
                                                    15, 0, 255, 255, 255);
    }
}

void Map::setGameHud() {
    this->gameHudRect.x = 0;
    this->gameHudRect.y = 0;
    this->gameHudRect.w = Map::getMap()->mapw;
    this->gameHudRect.h = 100;
}

void Map::addRabbit(std::shared_ptr<ForceDrivenEntity> rabbit) {
    this->rabbits.emplace_back(rabbit);
    this->moveables.emplace_back(rabbit);
}

std::vector<std::shared_ptr<GameObject>> &Map::getWaterTiles() {
    return waterTiles;
}

Mister &Map::getMrJansen() const {
    return *mrJansen;
}

Missus &Map::getMsJansen() const {
    return *msJansen;
}

const std::shared_ptr<Tile> &Map::getGrot() const {
    return grot;
}

void Map::removeRabbit(ForceDrivenEntity *rabbit) {
    int at = 0;
    for (auto &listrb : rabbits) {
        if (rabbit == listrb.get()) {
            this->deadrabbits.emplace_back(listrb);
            break;
        }
        at++;
    }
    this->rabbits.erase(rabbits.begin() + at);
}

void Map::refreshMoveables() {
    for (auto it = Map::getMap()->moveables.begin();
         it != Map::getMap()->moveables.end();) {
        if (!it->get()->isVisible())
            it = Map::getMap()->moveables.erase(it);
        else
            ++it;
    }
}

KmPoint Map::getRandomRabbitPoint() {
    if (!this->rabbits.empty()) {
        GameObject *r;
        if (rabbits.size() == 1) {
            r = rabbits.at(0).get();
        } else {
            int i = rand() % (this->rabbits.size() - 1) + 0;
            r = rabbits.at(i).get();
        }
        if (r->rect.getOriginX() < 0 || r->rect.getOriginX() > 1280 || r->rect.getOriginY() < 0 ||
            r->rect.getOriginY() > 720) {
            return getRandomGrassPoint();
        }
        return KmPoint(r->rect.getOriginX(), r->rect.getOriginY());
    }

    return getRandomGrassPoint();
}

Dog &Map::getDog() {
    return *this->dog;
}
