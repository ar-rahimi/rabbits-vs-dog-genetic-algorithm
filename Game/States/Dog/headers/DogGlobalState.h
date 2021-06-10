//
// Created by Mevlüt Özdemir on 20-12-17.
//

#ifndef TOETS_GLOBALSTATE_H
#define TOETS_GLOBALSTATE_H


#include <Dog.h>

class DogGlobalState : public State<Dog> {

private:
    int timeToIncreaseThirst;

public:
    DogGlobalState();

    void enterState(Dog &owner) override;

    void exitState(Dog &owner) override;

    void updateState(Dog &owner) override;

    std::string getName() const override;

    bool hasRabbitsWithin(Dog &owner, int pixels) const;
};

#endif //TOETS_GLOBALSTATE_H
