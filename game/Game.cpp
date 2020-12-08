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
    showGameWindow();
    simulate();
}

void Game::simulate() {
//    long long last_time = SoccerUtils::getCurrentTime();
    while(!is_goal){

        updateInput();
//        world->nextStep(elapsed_time);

        render();
    }

}

void Game::onGoal(bool inLeft) {
    is_goal = true;
}

void Game::render() {

}

void Game::updateInput() {

}

void Game::showGameWindow() {

}
