cmake_minimum_required(VERSION 3.17)
project(soccer)

set(CMAKE_CXX_STANDARD 14)
add_executable(soccer game/main.cpp game/Game.cpp game/Game.h game/World.cpp game/World.h game/Actor.cpp game/Actor.h game/Player.cpp game/Player.h game/Ball.cpp game/Ball.h game/Options.h game/SoccerUtils.h game/Position.cpp game/Position.h game/Speed.cpp game/Speed.h)