//
// Created by deliner on 07.12.2020.
//

#include "Game.h"
#include "SoccerUtils.h"
#include "Options.h"

Game::Game() {
    world = new World(this);
    is_goal = false;
    window = new GameWindow(sf::VideoMode(1280, 720), "Soccer");
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
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
//        if (!is_goal) {
        long long current_time = SoccerUtils::getCurrentTime();
        if ((current_time - last_time) > INPUT_TIME_UPDATE)
            updateInput();
        world->step();
//        }
        render();
    }
}

void Game::onGoal(bool inLeft) {
    is_goal = true;
}

void Game::render() {
    if (window->wasResized())
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
    float rect_x = (FIELD_X_SIZE) * scale_factor;
    float rect_y = (FIELD_Y_SIZE) * scale_factor;

    auto rect = sf::RectangleShape(Vector2f(rect_x, rect_y));
    rect.setOrigin(rect_x / 2, rect_y / 2);
    rect.setPosition(window_x / 2, window_y / 2);
    rect.setFillColor(Color(0, 0, 0, 0));
    rect.setOutlineThickness(LINE_SIZE * scale_factor/2);
    rect.setOutlineColor(Color(255, 255, 255));
    window->draw(rect);
}

void Game::renderGoal() {
    float rect_x = (GOAL_X_SIZE-LINE_SIZE/2) * scale_factor;
    float rect_y = GOAL_Y_SIZE * scale_factor;

    auto rect = sf::RectangleShape(Vector2f(rect_x, rect_y));
    rect.setFillColor(Color(0, 0, 0, 0));
    rect.setOutlineThickness(LINE_SIZE * scale_factor/2);
    rect.setOutlineColor(Color(255, 255, 255));

    rect.setOrigin(rect_x, rect_y / 2);
    rect.setPosition(window_x / 2 - (FIELD_X_SIZE + LINE_SIZE) * scale_factor / 2, window_y / 2);
    window->draw(rect);

    rect.setOrigin(0, rect_y / 2);
    rect.setPosition(window_x / 2 + (FIELD_X_SIZE + LINE_SIZE) * scale_factor / 2, window_y / 2);
    window->draw(rect);

}

void Game::renderBall() {
    b2Vec2 position = world->getBallPosition();
    float radius = BALL_SIZE * scale_factor / 2;
    float x_pos = position.x * scale_factor + window_x / 2;
    float y_pos = -position.y * scale_factor + window_y / 2;
//    printf("ball x: %f y: %f\n", x_pos, y_pos);
    auto ball = sf::CircleShape(radius, 360);
    ball.setOrigin(radius, radius);
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
    float radius = PLAYER_SIZE * scale_factor / 2;
    float x_pos = position.x * scale_factor + window_x / 2;
    float y_pos = -position.y * scale_factor + window_y / 2;

    auto player = sf::CircleShape(radius, 360);
    player.setOrigin(radius, radius);
    player.setPosition(x_pos, y_pos);
    player.setFillColor(inFirstTeam ? sf::Color(255, 0, 0) : sf::Color(0, 0, 255));
    window->draw(player);
}

void Game::updateWindowSettings() {
    auto size = window->getSize();
    window_x = size.x;
    window_y = size.y;

    sf::FloatRect area(0,0,window_x, window_y);
    window->setView(sf::View(area));

    // printf("x: %f y: %f\n", window_x, window_y);
    float x_scale = window_x / GAME_X_SIZE;
    float y_scale = window_y / GAME_Y_SIZE;
    scale_factor = std::min(x_scale, y_scale);
    // printf("scale_factor: %f %f %f\n", scale_factor, x_scale, y_scale);
}

