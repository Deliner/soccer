//
// Created by deliner on 07.12.2020.
//

#include "Ball.h"
#include "Options.h"

Ball *Ball::createBall(b2World *world) {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;

    b2CircleShape shape;
    shape.m_radius = BALL_SIZE / 2;

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;

    auto body = world->CreateBody(&bd);
    auto fixture = body->CreateFixture(&fd);
    return new Ball(body, fixture);
}

Ball::Ball(b2Body *body, b2Fixture *fixture) {
    this->body = body;
    this->fixture = fixture;
}

void Ball::setPosition(float x, float y) {
    b2Vec2 vec2(x, y);
    body->SetTransform(vec2, body->GetAngle());
}

b2Body *Ball::getBody() {
    return body;
}

b2Fixture *Ball::getFixture() {
    return fixture;
}

void Ball::addPunch(b2Vec2 force) {

}
