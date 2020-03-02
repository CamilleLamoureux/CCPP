cmake_minimum_required(VERSION 3.15)
project(final_project)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        Headers/Display.h
        Headers/Car.h
        Headers/Circuit.h
        Headers/Game.h)

set(PROJECT_SOURCES
        Sources/main.cpp
        Sources/Display.cpp
        Sources/Car.cpp
        Sources/Game.cpp Sources/Circuit.cpp)

add_executable(final_project ${PROJECT_SOURCES} ${PROJECT_HEADERS})