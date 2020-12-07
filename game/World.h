//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_WORLD_H
#define SOCCER_WORLD_H


#include "Player.h"
#include "Options.h"

class World {
public:
    class Callback;
public:
    void nextStep(long long mls);

private:
    Player player_array[2*PLAYER_PER_TEAM];
};

class World::Callback{
    virtual void onGoal() = 0;
};

#endif //SOCCER_WORLD_H
