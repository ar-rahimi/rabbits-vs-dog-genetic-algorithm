//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_DOGGOTORABBITSTATE_H
#define TOETS_DOGGOTORABBITSTATE_H


#include <Dog.h>

class DogCatchRabbitState : public State<Dog> {

public:
    void enterState(Dog &owner) override;

    void exitState(Dog &owner) override;

    void updateState(Dog &owner) override;

    std::string getName() const override;
};


#endif //TOETS_DOGGOTORABBITSTATE_H
