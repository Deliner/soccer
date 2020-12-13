//
// Created by deliner on 07.12.2020.
//

#ifndef SOCCER_GAME_H
#define SOCCER_GAME_H

#include "SFML/Graphics.hpp"
#include "World.h"
#include "GameWindow.h"

class Game : public World::Callback {

private:
    GameWindow *window;
    World *world;

    World::TeemData *first_team_data;
    World::TeemData *second_team_data;

    bool is_goal;

    float scale_factor;
    float window_x;
    float window_y;

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
