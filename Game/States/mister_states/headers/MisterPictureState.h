//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_MISTERPICTURESTATE_H
#define TOETS_MISTERPICTURESTATE_H


#include <Mister.h>

class MisterPictureState : public State<Mister> {

private:
    int millisecondsTillStateFinished;

public:
    MisterPictureState();

    void enterState(Mister &owner) override;

    void exitState(Mister &owner) override;

    void updateState(Mister &owner) override;

    std::string getName() const override;

    bool isStateFinished(Mister &owner) const;
};


#endif //TOETS_MISTERPICTURESTATE_H
