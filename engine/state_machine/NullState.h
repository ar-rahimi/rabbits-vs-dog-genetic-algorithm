//
// Created by Mevlüt Özdemir on 18-12-17.
//

#ifndef TOETS_NULLSTATE_H
#define TOETS_NULLSTATE_H


#include "State.h"

template<typename T>

class NullState : public State<T> {

public:
    NullState() = default;

    void enterState(T &owner) override {

    }

    void exitState(T &owner) override {

    }

    void updateState(T &owner) override {

    }

    std::string getName() const override {
        return "null state";
    }

};


#endif //TOETS_NULLSTATE_H
