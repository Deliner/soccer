//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_GAME_H
#define SOCCER_GAME_H


#include "World.h"

class Game: public World::Callback {

private:
    World *world;
    bool is_goal;

public:
    Game();
    void start();

private:
    void simulate();
    void render();
    void updateInput();
    virtual void onGoal();

};


#endif //SOCCER_GAME_H
