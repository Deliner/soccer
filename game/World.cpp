//
// Created by deliner on 07.12.2020.
//

#include "World.h"

World::World(World::Callback *callback) {
    this->callback = callback;
    world = new b2World(b2Vec2(0, 0));
    world->SetContactListener(this);

    initPLayersSpeeds();
    initPLayersPunches();
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

    bd2.position.Set(-(FIELD_X_SIZE + GOAL_X_SIZE) / 2, 0.0f);
    auto left_goal = world->CreateBody(&bd2);

    bd2.position.Set((FIELD_X_SIZE + GOAL_X_SIZE) / 2, 0.0f);
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
        for (int id = 0; id < (!team ? FIRST_TEAM_PLAYERS : SECOND_TEAM_PLAYERS); id++) {
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
                for (int id = 0; id < (!team ? FIRST_TEAM_PLAYERS : SECOND_TEAM_PLAYERS); id++) {
                    Player *player = (!team ? first_team : second_team)[id];
                    if (player->getPunchZone() == fixtureB) {
                        b2Vec2 *punch = (!team ? first_team_punches : second_team_punches)[id];
                        if (punch->x != 0)
                            ball->addPunch(*punch);
                        punch->SetZero();
                        break;
                    }
                }
            }
        }
    }
}

b2Vec2 World::getBallPosition() {
    return ball->getBody()->GetPosition();
}

void World::step() {
    updateWorldSpeeds();
    world->Step(60, 40, 40);
}

void World::setFirstTeamPosition(b2Vec2 *places) {
    for (int i = 0; i < FIRST_TEAM_PLAYERS; i++) {
        first_team[i]->setPosition(places[i]);
    }
}

void World::setSecondTeamPosition(b2Vec2 *places) {
    for (int i = 0; i < SECOND_TEAM_PLAYERS; i++) {
        second_team[i]->setPosition(places[i]);
    }
}

void World::initPLayersSpeeds() {
    for (int team = 0; team < 2; team++) {
        for (int id = 0; id < (!team ? FIRST_TEAM_PLAYERS : SECOND_TEAM_PLAYERS); id++) {
            auto *vec = new b2Vec2(0, 0);
            (!team ? first_team_speed : second_team_speed)[id] = vec;
        }
    }
}

void World::initPLayersPunches() {
    for (int team = 0; team < 2; team++) {
        for (int id = 0; id < (!team ? FIRST_TEAM_PLAYERS : SECOND_TEAM_PLAYERS); id++) {
            auto *vec = new b2Vec2(0, 0);
            (!team ? first_team_punches : second_team_punches)[id] = vec;
        }
    }
}

void World::updateWorldSpeeds() {
//    if (time - SoccerUtils::getCurrentTime() > 10) {
        for (int team = 0; team < 2; team++) {
            for (int id = 0; id < (!team ? FIRST_TEAM_PLAYERS : SECOND_TEAM_PLAYERS); id++) {
                (!team ? first_team : second_team)[id]->setSpeed(*((!team ? first_team_speed : second_team_speed)[id]));
            }
        }
//        time = SoccerUtils::getCurrentTime();
//    }
}

World::TeemData *World::getFirstTeemData() {
    return new World::TeemData(first_team, first_team_speed, first_team_punches, FIRST_TEAM_PLAYERS);
}

World::TeemData *World::getSecondTeemData() {
    return new World::TeemData(second_team, second_team_speed, second_team_punches, SECOND_TEAM_PLAYERS);
}

World::TeemData::TeemData(Player **players, b2Vec2 **speeds, b2Vec2 **punches, int length) {
    this->player_arr = players;
    this->player_speed_arr = speeds;
    this->player_punch_arr = punches;
    this->arr_length = length;
}
