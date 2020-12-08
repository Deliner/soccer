//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_PLAYER_H
#define SOCCER_PLAYER_H


#include <box2d/box2d.h>

class Player {

private:

    b2Body *body;
    b2Fixture *inner;
    b2Fixture *outer;
    int id;
    int team;
    float punch_x = 0;
    float punch_y = 0;

public:

    void setPosition(float x, float y);

    void setAngle(float angle);

    void setSpeed(float x, float y);

    b2Body *getBody();

    b2Fixture *getPunchZone();

    int getId();

    int getTeam();

    static Player *createPlayer(b2World *world, int id, int team);

    void setPunch(float x, float y);

    b2Vec2 getPunch();

private:

    Player(b2Body *body, b2Fixture *inner, b2Fixture *outer, int id, int team);


};


#endif //SOCCER_PLAYER_H
