cmake_minimum_required(VERSION 3.25)
project(ArkanoidWithoutAnEngine)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)
set(SDL2_PATH ${CMAKE_SOURCE_DIR}/modules/SDL2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(ArkanoidWithoutAnEngine source/entry_point/main.cpp source/entry_point/main.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
