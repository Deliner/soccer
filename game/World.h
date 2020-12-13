//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_WORLD_H
#define SOCCER_WORLD_H


#include "Player.h"
#include "Options.h"
#include "Ball.h"
#include "SoccerUtils.h"
#include <box2d/box2d.h>

class World : public b2ContactListener {
public:
    class Callback;

    struct TeemData;

public:
    World(World::Callback *callback);


    b2Vec2 getBallPosition();

    void setFirstTeamPosition(b2Vec2 places[FIRST_TEAM_PLAYERS]);

    void setSecondTeamPosition(b2Vec2 places[SECOND_TEAM_PLAYERS]);

    TeemData *getFirstTeemData();

    TeemData *getSecondTeemData();

    void step();

private:
    long  long time = SoccerUtils::getCurrentTime();

    Player *first_team[FIRST_TEAM_PLAYERS];
    Player *second_team[SECOND_TEAM_PLAYERS];

    b2Vec2 *first_team_speed[FIRST_TEAM_PLAYERS];
    b2Vec2 *second_team_speed[SECOND_TEAM_PLAYERS];

    b2Vec2 *first_team_punches[FIRST_TEAM_PLAYERS];
    b2Vec2 *second_team_punches[SECOND_TEAM_PLAYERS];

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

    void initPLayersSpeeds();

    void updateWorldSpeeds();

    void initPLayersPunches();
};

class World::Callback {
public:
    virtual void onGoal(bool inLeft) = 0;
};

struct World::TeemData {
    Player **player_arr;
    b2Vec2 **player_speed_arr;
    b2Vec2 **player_punch_arr;
    int arr_length;

    TeemData(Player **, b2Vec2 **, b2Vec2 **, int);
};

#endif //SOCCER_WORLD_H
