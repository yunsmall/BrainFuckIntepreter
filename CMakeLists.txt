cmake_minimum_required(VERSION 3.20)

project(brainfuck)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE CORE_SRC src/core/*.cpp)

add_executable(${PROJECT_NAME} src/main.cpp ${CORE_SRC})

add_executable(${PROJECT_NAME}_interpreter src/interpereter.cpp ${CORE_SRC})