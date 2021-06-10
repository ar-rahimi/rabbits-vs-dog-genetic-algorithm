//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_MISSUSWANDERSTATE_H
#define TOETS_MISSUSWANDERSTATE_H


#include <Missus.h>
#include <state_machine/State.h>

class MissusWanderState : public State<Missus> {


public:
    void enterState(Missus &owner) override;

    void exitState(Missus &owner) override;

    void updateState(Missus &owner) override;

    std::string getName() const override;

    bool nearbyRabbits(int pixels);
};

#endif //TOETS_MISSUSWANDERSTATE_H
