//
// Created by Mevlüt Özdemir on 20-12-17.
//

#ifndef TOETS_TIME_H
#define TOETS_TIME_H


class Seconds {

private:
    int seconds;

public:
    explicit Seconds(int seconds);

    int toMilliSeconds();

};


#endif //TOETS_TIME_H
