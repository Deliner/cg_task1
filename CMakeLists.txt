cmake_minimum_required(VERSION 3.17)
project(cg_task1)

set(CMAKE_CXX_STANDARD 14)

add_executable(cg_task1 main.cpp Game.cpp World.cpp GameTile.cpp TextureManager.cpp Level.cpp)