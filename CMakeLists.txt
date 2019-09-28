cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME SFML_Automata)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML-2.5.1/lib/cmake/SFML")

set(SOURCE_FILES main.cpp Game.cpp Game.h World.cpp World.h Creature.cpp Creature.h Entitymanager.cpp Entitymanager.h Util/RandomGenerator.cpp Util/RandomGenerator.h)

file(GLOB ALL_REQUIRED_DLL "libs/required_dlls/*.dll")
file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system )

