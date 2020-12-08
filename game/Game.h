//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_GAME_H
#define SOCCER_GAME_H

#include "SFML/Graphics.hpp"
#include "World.h"

class Game : public World::Callback {

private:
    sf::RenderWindow *window;
    World *world;

    bool is_goal;

    int scaleFactor;
    int window_x;
    int window_y;

public:
    Game();

    void start();

private:
    void simulate();

    void updateInput();

    void showGameWindow();

    void onGoal(bool inLeft) override;

    void render();

    void renderBackground();

    void renderField();

    void renderGoal();

    void renderBall();

    void renderPlayers();

    void renderPlayer(b2Vec2, float, bool inFirstTeam);

    void updateWindowSettings();
};


#endif //SOCCER_GAME_H
