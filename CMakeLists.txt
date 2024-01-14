cmake_minimum_required(VERSION 3.25)
project(ArkanoidWithoutAnEngine)

set(CMAKE_C_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)
set(SDL2_PATH ${CMAKE_SOURCE_DIR}/modules/SDL2)
set(SDL2_IMAGE_PATH ${CMAKE_SOURCE_DIR}/modules/SDL2_image)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

add_executable(ArkanoidWithoutAnEngine
        source/entry_point/main.cpp
        source/entry_point/application/application.cpp
        source/game/converters/converters.cpp
        source/game/dtos/vector2/int_vector2.cpp
        source/game/dtos/vector2/vector2.cpp
        source/game/dtos/window_references/window_references.cpp
        source/game/input/input.cpp
        source/game/level/constants/levels.cpp
        source/game/loop/game_loop.cpp
        source/game/platform/controller/platform_controller.cpp
        source/game/platform/model/platform.cpp
        source/game/platform/view/platform_view.cpp
        source/game/rendering/screen_applier.cpp
        source/game/rendering/screen_cleaner.cpp
        source/game/shortcuts/shortcuts.cpp
        source/game/game.cpp
        source/game/level/view/level_view.cpp
        source/game/level/level.cpp
        source/game/loop/time/average_game_time.cpp
        source/game/input/input.h
        source/game/input/key_type.h
        source/game/game_object/game_object.h
        source/game/dtos/window_references/window_references.h
        source/game/dtos/vector2/vector2.h
        source/game/dtos/vector2/int_vector2.h
        source/game/converters/converters.h
        source/entry_point/application/application.h
        source/game/level/constants/levels.h
        source/game/level/view/level_view.h
        source/game/level/level.h
        source/game/loop/time/average_game_time.h
        source/game/loop/time/game_time.h
        source/game/loop/time/read_only_game_time.h
        source/game/loop/updatables/events_updatable.h
        source/game/loop/updatables/updatable.h
        source/game/loop/game_loop.h
        source/game/platform/controller/platform_controller.h
        source/game/platform/model/platform.h
        source/game/platform/view/platform_view.h
        source/game/rendering/rendering_constants.h
        source/game/rendering/screen_applier.h
        source/game/rendering/screen_cleaner.h
        source/game/shortcuts/render_colors.h
        source/game/shortcuts/shortcuts.h
        source/game/game.h)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})
