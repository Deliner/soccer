//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_WORLD_H
#define SOCCER_WORLD_H


#include "Player.h"
#include "Options.h"
#include "Ball.h"
#include <box2d/box2d.h>

class World : public b2ContactListener {
public:
    class Callback;

public:
    World(World::Callback *callback);

    Player **getFirstTeam();
    Player **getSecondTeam();
    b2Vec2 getBallPosition();
    void step();

private:
    Player *first_team[PLAYER_PER_TEAM];
    Player *second_team[PLAYER_PER_TEAM];

    b2World *world = NULL;
    Ball *ball = NULL;
    b2Body *field = NULL;
    b2Fixture *left_goal_zone = NULL;
    b2Fixture *right_goal_zone = NULL;

    World::Callback *callback = NULL;

private:
    void createWorld();

    void createField();

    void createGoal();

    void createPlayers();

    void createBall();

    void BeginContact(b2Contact *contact) override;

};

class World::Callback {
public:
    virtual void onGoal(bool inLeft) = 0;
};

#endif //SOCCER_WORLD_H
