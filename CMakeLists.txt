cmake_minimum_required(VERSION 3.25)
project(ArkanoidWithoutAnEngine)

set(CMAKE_C_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)
set(SDL2_PATH ${CMAKE_SOURCE_DIR}/modules/SDL2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(ArkanoidWithoutAnEngine source/entry_point/main.cpp
        source/entry_point/application/application.cpp
        source/game/converters/converters.cpp
        source/game/dtos/vector2/int_vector2.cpp
        source/game/dtos/vector2/vector2.cpp
        source/game/dtos/window_handles/window_references.cpp
        source/game/input/input.cpp
        source/game/level/level_view.cpp
        source/game/levels/levels.cpp
        source/game/loop/game_loop.cpp
        source/game/platform/controller/platform_controller.cpp
        source/game/platform/model/platform.cpp
        source/game/platform/view/platform_view.cpp
        source/game/rendering/rendering_constants.cpp
        source/game/rendering/screen_applier.cpp
        source/game/rendering/screen_cleaner.cpp
        source/game/shortcuts/render_colors.cpp
        source/game/shortcuts/shortcuts.cpp
        source/game/shortcuts/render_colors.cpp
        source/game/game.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
