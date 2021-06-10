//
// Created by Mevlüt Özdemir on 20-12-17.
//

#ifndef TOETS_MISSUSIDLESTATE_H
#define TOETS_MISSUSIDLESTATE_H


#include <Missus.h>

class MissusIdleState : public State<Missus> {

public:
    void enterState(Missus &owner) override;

    void exitState(Missus &owner) override;

    void updateState(Missus &owner) override;

    std::string getName() const override;
};

#endif //TOETS_MISSUSIDLESTATE_H
