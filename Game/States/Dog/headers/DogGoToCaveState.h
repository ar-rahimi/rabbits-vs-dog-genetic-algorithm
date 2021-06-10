//
// Created by Mevlüt Özdemir on 25-12-17.
//

#ifndef TOETS_DOGGOTOCAVE_H
#define TOETS_DOGGOTOCAVE_H


#include <Dog.h>

class DogGoToCaveState : public State<Dog> {

public:
    void enterState(Dog &owner) override;

    void exitState(Dog &owner) override;

    void updateState(Dog &owner) override;

    std::string getName() const override;
};

#endif //TOETS_DOGGOTOCAVE_H
