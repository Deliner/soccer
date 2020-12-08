//
// Created by deliner on 07.12.2020.
//

#include "World.h"

World::World(World::Callback *callback) {
    this->callback = callback;
    world = new b2World(b2Vec2(0.0, 0.0));
    world->SetContactListener(this);
    createWorld();
}

void World::createWorld() {
    createField();
    createGoal();
    createPlayers();
    createBall();
}

void World::createField() {
    b2BodyDef bd;
    field = world->CreateBody(&bd);

    b2EdgeShape shape;

    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, -FIELD_Y_SIZE / 2), b2Vec2(FIELD_X_SIZE / 2, -FIELD_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, FIELD_Y_SIZE / 2), b2Vec2(FIELD_X_SIZE / 2, FIELD_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, -FIELD_Y_SIZE / 2), b2Vec2(FIELD_X_SIZE / 2, -GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, FIELD_Y_SIZE / 2), b2Vec2(FIELD_X_SIZE / 2, GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, -FIELD_Y_SIZE / 2), b2Vec2(FIELD_X_SIZE / 2, -GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, FIELD_Y_SIZE / 2), b2Vec2(FIELD_X_SIZE / 2, GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, GOAL_Y_SIZE / 2), b2Vec2((FIELD_X_SIZE / 2 + GOAL_X_SIZE), GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2((FIELD_X_SIZE / 2 + GOAL_X_SIZE), GOAL_Y_SIZE / 2), b2Vec2((FIELD_X_SIZE / 2 + GOAL_X_SIZE), -GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, -GOAL_Y_SIZE / 2), b2Vec2((FIELD_X_SIZE / 2 + GOAL_X_SIZE), -GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, GOAL_Y_SIZE / 2), b2Vec2(-(FIELD_X_SIZE / 2 + GOAL_X_SIZE), GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(-(FIELD_X_SIZE / 2 + GOAL_X_SIZE), GOAL_Y_SIZE / 2), b2Vec2(-(FIELD_X_SIZE / 2 + GOAL_X_SIZE), -GOAL_Y_SIZE / 2));
    field->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(FIELD_X_SIZE / 2, -GOAL_Y_SIZE / 2), b2Vec2(-(FIELD_X_SIZE / 2 + GOAL_X_SIZE), -GOAL_Y_SIZE / 2));
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
    shape2.SetAsBox(GOAL_X_SIZE / 2, GOAL_Y_SIZE / 2);

    b2FixtureDef fd;
    fd.isSensor = true;
    fd.shape = &shape2;

    left_goal_zone = left_goal->CreateFixture(&fd);
    right_goal_zone = right_goal->CreateFixture(&fd);
}

void World::createPlayers() {
    for (int team = 0; team < 2; team++) {
        for (int id = 0; id < PLAYER_PER_TEAM; id++) {
            (!team ? first_team : second_team)[id] = Player::createPlayer(world, id, team);
        }
    }
}

void World::createBall() {
    ball = Ball::createBall(world);
}

void World::BeginContact(b2Contact *contact) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();
    b2Fixture *buf;

    if (fixtureB == ball->getFixture()) {
        buf = fixtureA;
        fixtureA = fixtureB;
        fixtureB = buf;
    }
    if (fixtureA == ball->getFixture()) {
        if (fixtureB == left_goal_zone)
            callback->onGoal(true);
        else if (fixtureB == right_goal_zone)
            callback->onGoal(false);
        else {
            for (int team = 0; team < 2; team++) {
                for (int id = 0; id < PLAYER_PER_TEAM; id++) {
                    Player *player = (!team ? first_team : second_team)[id];
                    if (player->getPunchZone() == fixtureB) {
                        ball->addPunch(player->getPunch());
                        break;
                    }
                }
            }
        }
    }
}

Player **World::getFirstTeam() {
    return first_team;
}

Player **World::getSecondTeam() {
    return second_team;
}

b2Vec2 World::getBallPosition() {
    return ball->getBody()->GetPosition();
}

void World::step() {
    world->Step(60, 8, 8);
}
