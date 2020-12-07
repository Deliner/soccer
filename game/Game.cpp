//
// Created by deliner on 07.12.2020.
//

#include "Game.h"
#include "SoccerUtils.h"

Game::Game() {
    world = new World();
    is_goal = false;
}

void Game::start() {
    simulate();
}

void Game::simulate() {
    long long last_time = SoccerUtils::getCurrentTime();
    while(!is_goal){

        updateInput();

        long long current_time = SoccerUtils::getCurrentTime();
        long long elapsed_time = current_time - last_time;
        world->nextStep(elapsed_time);

        render();
    }

}

void Game::onGoal() {
    is_goal = true;
}

void Game::render() {

}

void Game::updateInput() {

}
