//
// Created by deliner on 07.12.2020.
//

#include "Player.h"
#include "Options.h"


Player::Player(b2Body *body, b2Fixture *inner, b2Fixture *outer, int id, int team) {
    this->body = body;
    this->id = id;
    this->team = team;
    this->inner = inner;
    this->outer = outer;
}

Player *Player::createPlayer(b2World *world, int id, int team) {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;

    b2CircleShape inner;
    inner.m_radius = PLAYER_SIZE / 2;

    b2CircleShape outer;
    inner.m_radius = PLAYER_SIZE;

    b2FixtureDef in_fd;
    in_fd.shape = &inner;
    in_fd.density = 0.0f;

    b2FixtureDef out_fd;
    out_fd.shape = &outer;
    out_fd.isSensor = true;

    auto body = world->CreateBody(&bd);
    auto in_fixture = body->CreateFixture(&in_fd);
    auto out_fixture = body->CreateFixture(&out_fd);

    return new Player(body, in_fixture, out_fixture, id, team);
}

int Player::getTeam() {
    return team;
}

int Player::getId() {
    return id;
}

b2Body *Player::getBody() {
    return body;
}

void Player::setPunch(float x, float y) {
    punch_x = x;
    punch_y = y;
}

b2Vec2 Player::getPunch() {
    return {punch_x, punch_y};
}

void Player::setAngle(float angle) {
    body->SetTransform(body->GetPosition(), angle);
}

void Player::setPosition(b2Vec2 vec) {
    body->SetTransform(vec, body->GetAngle());
}

void Player::setSpeed(b2Vec2 vec) {
    body->SetLinearVelocity(b2Vec2(50 * (rand() % 2 ? -1 : 1), 50 * (rand() % 2 ? -1 : 1)));
}

b2Fixture *Player::getPunchZone() {
    return outer;
}
