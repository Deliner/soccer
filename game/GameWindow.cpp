//
// Created by deliner on 09.12.2020.
//

#include "GameWindow.h"

void GameWindow::onResize() {
    RenderWindow::onResize();
    was_resized = true;
}

bool GameWindow::wasResized() {
    bool buf = was_resized;
    was_resized = false;
    return buf;
}