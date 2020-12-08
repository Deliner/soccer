//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_WORLD_H
#define SOCCER_WORLD_H


#include "Player.h"
#include "Options.h"
#include "Ball.h"
#include <box2d/box2d.h>

class World {
public:
    class Callback;
public:
    World();
    void nextStep(long long mls);

private:
    b2World *world;
    Player *first_team;
    Player *second_team;
    Ball *ball;
    b2Body *field;
    b2Fixture *left_goal_zone;
    b2Fixture *right_goal_zone;


private:
    void initWorld();
    void createField();
    void createGoal();

};

class World::Callback{
    virtual void onGoal() = 0;
};

#endif //SOCCER_WORLD_H
