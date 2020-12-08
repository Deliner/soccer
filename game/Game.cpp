//
// Created by deliner on 07.12.2020.
//

#include "Game.h"
#include "SoccerUtils.h"
#include "Options.h"

Game::Game() {
    world = new World(this);
    is_goal = false;
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Soccer");
    window->setFramerateLimit(60);
}

void Game::start() {
    window->display();
    showGameWindow();
    updateWindowSettings();
    simulate();
}

void Game::simulate() {
    long long last_time = SoccerUtils::getCurrentTime();
    while (window->isOpen()) {
        while (!is_goal && window->isOpen()) {
            long long current_time = SoccerUtils::getCurrentTime();
            if ((current_time - last_time) > INPUT_TIME_UPDATE)
                updateInput();
            world->step();
            render();
        }
    }
}

void Game::onGoal(bool inLeft) {
    is_goal = true;
}

void Game::render() {
    updateWindowSettings();
    renderBackground();
    renderBall();
    renderPlayers();
    window->display();
}

void Game::updateInput() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Game::showGameWindow() {

}

void Game::renderBackground() {
    window->clear(sf::Color(0, 255, 0));
    renderField();
    renderGoal();
}

void Game::renderField() {

}

void Game::renderGoal() {

}

void Game::renderBall() {
    b2Vec2 position = world->getBallPosition();
    int x_pos = position.x * scaleFactor + window_x / 2;
    int y_pos = position.y * scaleFactor + window_y / 2;

    auto ball = sf::CircleShape(BALL_SIZE * scaleFactor / 2, 120);
    ball.setPosition(x_pos, y_pos);
    ball.setFillColor(sf::Color(128, 128, 128));
    window->draw(ball);
}

void Game::renderPlayers() {
    Player **first_team = world->getFirstTeam();
    Player **second_team = world->getSecondTeam();
    for (int team = 0; team < 2; team++) {
        for (int id = 0; id < PLAYER_PER_TEAM; id++) {
            auto player = (!team ? first_team : second_team)[id];
            renderPlayer(player->getBody()->GetPosition(), player->getBody()->GetAngle(), !team);
        }
    }
}

void Game::renderPlayer(b2Vec2 position, float angle, bool inFirstTeam) {
    int x_pos = position.x * scaleFactor + window_x / 2;
    int y_pos = position.y * scaleFactor + window_y / 2;

    auto player = sf::CircleShape(PLAYER_SIZE * scaleFactor / 2, 120);
    player.setPosition(x_pos, y_pos);
    player.setFillColor(inFirstTeam ? sf::Color(255, 0, 0) : sf::Color(0, 0, 255));
    window->draw(player);
}

void Game::updateWindowSettings() {
    auto size = window->getSize();
    window_x = size.x;
    window_y = size.y;

    int x_scale = window_x / (int) GAME_X_SIZE;
    int y_scale = window_y / (int) GAME_Y_SIZE;
    scaleFactor = std::min(x_scale, y_scale);
}
