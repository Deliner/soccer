//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_BALL_H
#define SOCCER_BALL_H

#include <box2d/box2d.h>

class Ball {

private:
    b2Body *body;
    b2Fixture *fixture;

    Ball(b2Body *, b2Fixture *);

public:
    void setPosition(float x, float y);

    void addPunch(b2Vec2 force);

    b2Body *getBody();
    b2Fixture *getFixture();

    static Ball *createBall(b2World *world);

};


#endif //SOCCER_BALL_H
