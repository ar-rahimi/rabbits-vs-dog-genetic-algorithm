//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_STATE_H
#define TOETS_STATE_H

#include <string>

template<typename T>

struct State {

public:
    virtual void enterState(T &owner) = 0;

    virtual void exitState(T &owner) = 0;

    virtual void updateState(T &owner) = 0;

    virtual std::string getName() const = 0;
};


#endif //TOETS_STATE_H
