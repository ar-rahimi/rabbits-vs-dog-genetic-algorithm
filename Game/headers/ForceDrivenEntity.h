//
// Created by Ahmad Rahimi on 12/20/17.
//

#ifndef TOETS_RABBIT3_H
#define TOETS_RABBIT3_H

#include <cmath>
#include <Helper.h>
#include <headers/FPoint.h>
#include <MoveableObject.h>
#include <vector>

class ForceDrivenEntity : public MoveableObject {
public:
    ForceDrivenEntity(int x, int y, int w, int h, int *color);
    int test = 22;
    //resultaat van acceleratie toeveogen aan force en deze vervolgens naar rectangle updaten
    void update(float time);

protected:

    //naar target gaan
    void seek(FPoint target, float maxSpeed = 0.1, float steeringLimit = 0.01);
    //target bereikt
    FPoint arrive(FPoint target, FPoint location, FPoint velocity, float distance, float maxSpeed);

    virtual void calcAndApplyForces();

    //force driven variables and functionaliteiten
    //maximale snelheid
    float maxSpeed = 0.1;
    //wanneer arrive wordt ingeschakeld
    float deaccelerationDistance = 150;

    FPoint acceleration;
    FPoint velocity;
    FPoint target;
    std::shared_ptr<Tile> targetTile;
    bool atTarget = true;

    FPoint align(std::vector<std::shared_ptr<GameObject>> alignWith, float limitBY, float aligningDistance);
    FPoint seperate(std::vector<std::shared_ptr<GameObject>> objects, float maxSpeed, float steering, float seperationDistance);
    FPoint cohesion(std::vector<std::shared_ptr<GameObject>> objects, float cohesionDistance);

    //ga en draai naar target
    FPoint steer(FPoint target, FPoint location, FPoint velocity, float maxSpeed);

    //force toevoegen aan acceleratie
    void applyForce(FPoint force);

    //normaliseren en snelheid toevoegen
    FPoint setMagnitude(FPoint vector, float speed);
    FPoint normalize(FPoint vector);
    //vector snelheid aanpassen
    FPoint limit(FPoint vector, float limitBy);
};


#endif //TOETS_RABBIT3_H