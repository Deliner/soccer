project(soccer)

add_link_options(-lbox2d -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system)

add_executable(soccer game/main.cpp game/Ball.cpp game/GameWindow.cpp game/Player.cpp game/World.cpp game/Game.cpp game/SoccerUtils.h)