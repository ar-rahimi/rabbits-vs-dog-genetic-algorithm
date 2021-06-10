//
// Created by Mevlüt Özdemir on 30-10-17.
//

#ifndef HANDELGAME_2_RANDOM_H
#define HANDELGAME_2_RANDOM_H

class Random {

public:
    int nextInt(int max) const;

    int nextInt(int min, int max) const;

    int getRandom(int min, int max) const;
};


#endif //HANDELGAME_2_RANDOM_H
