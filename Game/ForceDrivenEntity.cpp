//
// Created by Ahmad Rahimi on 12/20/17.
//

#include "ForceDrivenEntity.h"
#include "Rabbit.h"

ForceDrivenEntity::ForceDrivenEntity(int x, int y, int w, int h, int *color) : MoveableObject(x, y, w, h, color), target(0,0), velocity(0,0), acceleration(0,0) {
}

void ForceDrivenEntity::seek(FPoint target, float maxSpeed, float steeringLimit) {
    float distance = Helper::distanceBetweenPoints(target.x, target.y, this->rect.getX(), this->rect.getY());
    FPoint steering = {0,0};
    if(distance > deaccelerationDistance) {
        steering = this->steer(target, FPoint(this->rect.getX(), this->rect.getY()), this->velocity, maxSpeed);
    }else{
        steering = this->arrive(target, FPoint(this->rect.getX(), this->rect.getY()), this->velocity, distance, maxSpeed);
    }
    steering = this->limit(steering, steeringLimit);
    this->applyForce(steering);
}


FPoint ForceDrivenEntity::arrive(FPoint target, FPoint location, FPoint velocity, float distance, float maxSpeed) {
    FPoint desired = {target.x - location.x, target.y - location.y};
    float speed = Helper::map(distance, 0,deaccelerationDistance,0,maxSpeed);
    desired = this->setMagnitude(desired, speed);
    return desired-velocity;
}

FPoint ForceDrivenEntity::steer(FPoint target, FPoint location, FPoint velocity, float maxSpeed) {
    FPoint desired = {target.x - location.x, target.y - location.y};
    desired = this->setMagnitude(desired, maxSpeed);
    return desired-velocity;
}

FPoint ForceDrivenEntity::limit(FPoint vector, float limitBy) {
    return FPoint(vector.x*limitBy, vector.y*limitBy);
}

FPoint ForceDrivenEntity::setMagnitude(FPoint vector, float speed) {
    if(speed == 0)
        return {0,0};
    FPoint normalized = normalize(vector);
    return limit(normalized,speed);
}

FPoint ForceDrivenEntity::normalize(FPoint vector) {
    float squareX = vector.x * vector.x;
    float squareY = vector.y * vector.y;
    float squarerooted = std::sqrt(squareX + squareY);
    return {vector.x / squarerooted, vector.y / squarerooted};
}

void ForceDrivenEntity::update(float time) {
    this->acceleration = {0,0};

    this->calcAndApplyForces();

    this->velocity += acceleration;
    timeCounter += time;
    float dX = velocity.x;
    float dY = velocity.y;
    dX = dX * time;
    dY = dY * time;
    rect.setX(rect.getX() + dX);
    rect.setY(rect.getY() + dY);
}

void ForceDrivenEntity::applyForce(FPoint force) {
    acceleration += force;
}

FPoint ForceDrivenEntity::align(std::vector<std::shared_ptr<GameObject>> alignWith, float limitBY,  float aligningDistance) {
    FPoint alignP = {0,0};
    int count = 0;
    for(auto const &neigbour : alignWith){
        //verandert van rabbit naar forcedrivenentity op het eind
        ForceDrivenEntity* rabbitneigbour = dynamic_cast<ForceDrivenEntity*>(neigbour.get());
        float distance = Helper::distanceBetweenPoints(neigbour->rect.getX(), neigbour->rect.getY(), this->rect.getX(), this->rect.getY());
        if(neigbour.get() != this &&  distance < aligningDistance && distance > 0){
            alignP.x += rabbitneigbour->velocity.x;
            alignP.y += rabbitneigbour->velocity.y;
            count++;
        }
    }
    if(count != 0 && alignP.x != 0 && alignP.y != 0) {
        alignP.x /= (count);
        alignP.y /= (count);
        //normaliseer de align vector
        alignP = normalize(alignP);
        //limiteer de steering snelheid
        alignP = limit(alignP, limitBY);//0.01);
    }
    return alignP;
}

FPoint ForceDrivenEntity::seperate(std::vector<std::shared_ptr<GameObject>> objects, float maxSpeed, float steering, float seperationDistance) {
    FPoint seperateP = {0,0};
    int count = 0;
    for(auto &neighbour: objects){
        float distance = Helper::distanceBetweenPoints(neighbour->rect.getX(), neighbour->rect.getY(), this->rect.getX(), this->rect.getY());
        if(neighbour.get() != this &&  distance < seperationDistance && distance > 0){
            FPoint diff = {this->rect.getX() - neighbour->rect.getX(), this->rect.getY() - neighbour->rect.getY()};
            diff = normalize(diff);
            diff.x /= distance;
            diff.y /= distance;
            seperateP += diff;
            count++;
        }
    }
    if (count != 0 && seperateP.x != 0 && seperateP.y != 0) {
        //verklein de groote van de vector
        seperateP = setMagnitude(seperateP, maxSpeed);
        //normalizeer de vector
        seperateP = normalize(seperateP);
        //limiteer steering snelheid
        seperateP = limit(seperateP, steering);
    }
    return seperateP;
}

//template<typename InputIterator>
FPoint ForceDrivenEntity::cohesion(std::vector<std::shared_ptr<GameObject>> objects, float cohesionDistance) {
    FPoint cohesionP = {0,0};
    int count = 0;
    for(auto &neighbour: objects){
        float distance = Helper::distanceBetweenPoints(neighbour->rect.getX(), neighbour->rect.getY(), this->rect.getX(),
                                                       this->rect.getY());
        if (neighbour.get() != this && distance < cohesionDistance && distance > 0) {
            cohesionP += FPoint(neighbour->rect.getX(), neighbour->rect.getY());
            count++;
        }
    }
    if (count != 0 && cohesionP.x != 0 && cohesionP.y != 0) {
        cohesionP.x /= count;
        cohesionP.y /= count;
    }
    return cohesionP;
}

void ForceDrivenEntity::calcAndApplyForces() {

}
