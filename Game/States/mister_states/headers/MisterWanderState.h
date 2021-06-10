//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_MISTERWANDERSTATE_H
#define TOETS_MISTERWANDERSTATE_H


#include <state_machine/State.h>
#include <Mister.h>


class MisterWanderState : public State<Mister> {

private:
    int millisecondsTillPictureState;

public:
    MisterWanderState();

    void enterState(Mister &owner) override;

    void exitState(Mister &owner) override;

    void updateState(Mister &owner) override;

    std::string getName() const override;

    bool isTimeForPictureState(Mister &owner) const;
};

#endif //TOETS_MISTERWANDERSTATE_H
