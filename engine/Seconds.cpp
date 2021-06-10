//
// Created by Mevlüt Özdemir on 20-12-17.
//

#include "headers/Seconds.h"

Seconds::Seconds(int seconds) : seconds{seconds} {

}

int Seconds::toMilliSeconds() {
    return this->seconds * 1000;
}
