//
// Created by Ahmad Rahimi on 12/23/17.
//
#include "Rabbit.h"
#include "headers/FPoint.h"

Rabbit::Rabbit(int x, int y, int w, int h, int *color, Chromosome chromosome) : ForceDrivenEntity(x, y, w, h, color) {
    this->setAttractedToSheep(chromosome.getAttractionDog());
    this->setCohesionToRabbits(chromosome.getAffectionCohesion());
    this->setAttractedToWater(chromosome.getAttractionWater());
    this->setSeperationFromRabbits(chromosome.getAffectionSeperation());
    this->setAlignmentWithRabbits(chromosome.getAffectionAlignment());
}

void Rabbit::calcAndApplyForces() {
    attractToSheep();
    coheseToRabbits();
    attractToWater();
    seperateFromRabbits();
    alignWithRabbits();
    ForceDrivenEntity::calcAndApplyForces();
}

//sheep attraction
void Rabbit::attractToSheep() {
    if (this->attractedToSheep["attracted"]) {
        this->seek(Map::getMap()->dog->getPoint(), attractedToSheep["maxSpeed"], attractedToSheep["steering"]);
    } else {
        std::vector<std::shared_ptr<GameObject>> dog;
        dog.emplace_back(Map::getMap()->dog);

        FPoint p = this->seperate(dog, this->attractedToSheep["maxSpeed"], this->attractedToSheep["steering"], this->attractedToSheep["affectionDistance"]);
        if(p.x != 0 || p.y != 0)
            seperatedFromDogCount++;
        this->velocity += p;
    }
}

void Rabbit::setAttractedToSheep(float attraction) {
    this->attractedToSheep["input"] = attraction;
    if (attraction > 0.0) {
        float inmax = 1.0;
        float inmin = 0.0;
        float outmax = 0.1;
        float outmin = 0.0;
        float out = Helper::map(attraction, inmin, inmax, outmin, outmax);
        this->attractedToSheep["maxSpeed"] = out;
        this->attractedToSheep["steering"] = static_cast<float>(out / 10.0);
        this->attractedToSheep["attracted"] = true;
    } else {
        float in = abs(attraction);
        float inmax = 1.0;
        float inmin = 0.0;
        float outmax = 0.1;
        float outmin = 0.0;
        float out = Helper::map(in, inmin, inmax, outmin, outmax);
        this->attractedToSheep["maxSpeed"] = out/2;
        this->attractedToSheep["steering"] = static_cast<float>(out / 2.0);
        this->attractedToSheep["affectionDistance"] = out * 500;
        this->attractedToSheep["attracted"] = false;
    }

}

void Rabbit::coheseToRabbits() {
    FPoint p = this->cohesion(Map::getMap()->rabbits, this->affectedCohesion["affectionDistance"]);
    if (p.x != 0 || p.y != 0) {
        this->seek(p, this->affectedCohesion["maxSpeed"], this->affectedCohesion["steering"]);
    }
}

void Rabbit::setCohesionToRabbits(float cohesionForce) {
    this->affectedCohesion["input"] = cohesionForce;
    float inmax = 1.0;
    float inmin = 0.0;
    float outmax = 0.1;
    float outmin = 0.001;
    float out = Helper::map(cohesionForce, inmin, inmax, outmin, outmax);

    this->affectedCohesion["maxSpeed"] = out;
    this->affectedCohesion["steering"] = static_cast<float>(out / 10.0);
    this->affectedCohesion["affectionDistance"] = 100;
}

void Rabbit::attractToWater() {
    if (this->attractedToWater["attracted"]) {
        FPoint p = this->cohesion(Map::getMap()->getWaterTiles(), this->attractedToWater["affectionDistance"]);
        if (p.x != 0 || p.y != 0) {
            this->seek(p, this->attractedToWater["maxSpeed"], this->attractedToWater["steering"]);
        }
    } else {
        FPoint p = this->seperate(Map::getMap()->getWaterTiles(), this->attractedToWater["maxSpeed"],
                                  this->attractedToWater["steering"], this->attractedToWater["affectionDistance"]);
        this->velocity += p;
    }
}

void Rabbit::setAttractedToWater(float attraction) {
    this->attractedToWater["input"] = attraction;
    float inmax = 1.0;
    float inmin = 0.0;
    float outmax = 0.15;
    float outmin = 0.0;
    if (attraction > 0.0) {
        float out = Helper::map(attraction, inmin, inmax, outmin, outmax);
        this->attractedToWater["maxSpeed"] = out;
        this->attractedToWater["steering"] = static_cast<float>(out / 10.0);
        this->attractedToWater["affectionDistance"] = 250;
        this->attractedToWater["attracted"] = true;
    } else {
        float in = abs(attraction);
        float out = Helper::map(in, inmin, inmax, outmin, outmax);
        this->attractedToWater["maxSpeed"] = out;
        this->attractedToWater["steering"] = static_cast<float>(out / 5.0);
        this->attractedToWater["affectionDistance"] = out * 350;
        this->attractedToWater["attracted"] = false;
    }
}

void Rabbit::setSeperationFromRabbits(float seperationForce) {
    this->affectedSeperation["input"] = seperationForce;
    float in = abs(seperationForce);
    float inmax = 1.0;
    float inmin = 0.0;
    float outmax = 0.02;
    float outmin = 0.005;
    float out = Helper::map(in, inmin, inmax, outmin, outmax);
    this->affectedSeperation["maxSpeed"] = out;
    this->affectedSeperation["steering"] = out;
    this->affectedSeperation["affectionDistance"] = out * 400;
    if (this->affectedSeperation["affectionDistance"] < 10) {
        this->affectedSeperation["affectionDistance"] = 10;
    }
}

void Rabbit::seperateFromRabbits() {
    FPoint p = this->seperate(Map::getMap()->rabbits, this->affectedSeperation["maxSpeed"],
                              this->affectedSeperation["steering"], this->affectedSeperation["affectionDistance"]);
    this->velocity += p;
}

void Rabbit::alignWithRabbits() {
    FPoint p = this->align(Map::getMap()->rabbits, this->affectedAlignment["limitBy"],
                           this->affectedAlignment["affectionDistance"]);
    this->velocity += p;
}

void Rabbit::setAlignmentWithRabbits(float alignment) {
    if (alignment > 1.0) {
        alignment = 1.0;
    } else if (alignment < 0.0) {
        alignment = 0.0;
    }
    this->affectedAlignment["input"] = alignment;
    float inmax = 1.0;
    float inmin = 0.0;
    float outmax = 0.001;
    float outmin = 0.0001;
    float out = Helper::map(alignment, inmin, inmax, outmin, outmax);
    this->affectedAlignment["limitBy"] = out;
    this->affectedAlignment["affectionDistance"] = 100;
}

void Rabbit::updateFitness(float updateBy) {
    if(visible) {
        timeSurvived += updateBy/1000;
    }
}

int Rabbit::getFitness() {
    int fitness = timeSurvived;
    if(isVisible()){
        fitness += 5;
        if(chased > 0) {
            fitness += (chased * (chased*5));
            fitness += seperatedFromDogCount*5;
        }
    }else {
        fitness -= 5;
        if(chased > 0 && seperatedFromDogCount < 10){
            //fitness aangepast eerder was dit (seperatedFromDogCount)*2;
            fitness -= (10-seperatedFromDogCount)*2;
        } else{
            fitness += seperatedFromDogCount*2;
        }
        fitness += (chased * (chased*2));
    }
    return fitness;
}

void Rabbit::update(float time) {
    shouldDie();
    updateFitness(time);
    ForceDrivenEntity::update(time);
}


void Rabbit::shouldDie(){
    if(visible) {
        visible = (this->rect.getX() > 0 && this->rect.getX() < 1280 && rect.getY() > 0 && rect.getY() < 720);
        if(visible) {
            visible = Map::getMap()->getTileAtPosition(KmPoint(this->rect.getX(), this->rect.getY()))->tiletype !=
                      Tile::WATER;
            if (visible) {
                Dog *dog = Map::getMap()->dog.get();
                visible = Helper::distanceBetweenPoints(this->rect.getOriginX(), this->rect.getOriginY(),
                                                        dog->rect.getOriginX(), dog->rect.getOriginY()) > 15;
            }
            if (!visible)
                Map::getMap()->removeRabbit(this);
        }
    }
}

void
Rabbit::setVariables(float attractedToSheep, float attractedToWater, float affectedCohesion, float affectedSeperation,
                     float affectedAlignment) {
    this->setAlignmentWithRabbits(affectedAlignment);
    this->setSeperationFromRabbits(affectedSeperation);
    this->setCohesionToRabbits(affectedCohesion);
    this->setAttractedToWater(attractedToWater);
    this->setAttractedToSheep(attractedToSheep);
}

void Rabbit::increaseChase() {
    chased++;
}

Chromosome Rabbit::getChromosome() {
    return Chromosome(this->affectedCohesion["input"],
               this->affectedAlignment["input"],
               this->affectedSeperation["input"],
               this->attractedToWater["input"],
               this->attractedToSheep["input"],
               this->getFitness());
}

