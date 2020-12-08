//
// Created by deliner on 07.12.2020.
//

#include "World.h"

void World::nextStep(long long mls) {

}

World::World() {
    first_team = new Player[PLAYER_PER_TEAM];
    second_team = new Player[PLAYER_PER_TEAM];

    b2Body
}

void World::initWorld() {
    world = new b2World(b2Vec2(0.0, 0.0));
    createField();
}

void World::createField() {
    b2BodyDef bd;
    field = world->CreateBody(&bd);

    b2EdgeShape shape;

    shape.SetTwoSided(b2Vec2(-55.0f, -35.0f), b2Vec2(55.0f, -35.0f));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(-55.0f, 35.0f), b2Vec2(55.0f, 35.0f));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(-55.0f, -35.0f), b2Vec2(-55.0f, -3.5f));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(-55.0f, 35.0f), b2Vec2(-55.0f, 3.5f));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(55.0f, -35.0f), b2Vec2(55.0f, -3.5f));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(55.0f, 35.0f), b2Vec2(55.0f, 3.5f));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(55.0f, 3.5f), b2Vec2(57.0f, 3.5f));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(57.0f, 3.5f), b2Vec2(57.0f, -3.5f));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(55.0f, -3.5f), b2Vec2(57.0f, -3.5f));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(-55.0f, 3.5f), b2Vec2(-57.0f, 3.5f));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(-57.0f, 3.5f), b2Vec2(-57.0f, -3.5f));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(-55.0f, -3.5f), b2Vec2(-57.0f, -3.5f));
    field->CreateFixture(&shape, 0.0f);
}

void World::createGoal() {
    b2BodyDef bd2;
    bd2.type = b2_staticBody;

    bd2.position.Set(-56.0f, 0.0f);
    auto left_goal = world->CreateBody(&bd2);

    bd2.position.Set(56.0f, 0.0f);
    auto right_goal = world->CreateBody(&bd2);

    b2PolygonShape shape2;
    shape2.SetAsBox(1.0f, 3.5f);

    b2FixtureDef fd;
    fd.isSensor = true;
    fd.shape = &shape2;

    left_goal_zone = left_goal->CreateFixture(&fd);
    right_goal_zone = right_goal->CreateFixture(&fd);
}
