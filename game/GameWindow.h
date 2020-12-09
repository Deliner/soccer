//
// Created by deliner on 09.12.2020.
//

#ifndef SOCCER_GAMEWINDOW_H
#define SOCCER_GAMEWINDOW_H

#include "SFML/Graphics.hpp"

using namespace sf;

class GameWindow : public sf::RenderWindow {


private:
    bool was_resized = true;
public:
    void onResize() override;

    bool wasResized();

    GameWindow(VideoMode mode, const String &title, Uint32 style = Style::Default, const ContextSettings &settings = ContextSettings()) : RenderWindow(mode, title, style, settings) {}
};

#endif //SOCCER_GAMEWINDOW_H
