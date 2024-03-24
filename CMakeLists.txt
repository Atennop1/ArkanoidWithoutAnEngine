cmake_minimum_required(VERSION 3.22.1)
project(ArkanoidWithoutAnEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)
set(CMAKE_PREFIX_PATH ${CMAKE_MODULE_PATH})

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
else()
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --static -std=c++0x")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

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
        source/game/level/constants/level_maps.cpp
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
        source/game/dtos/window_references/window_references.h
        source/game/dtos/vector2/vector2.h
        source/game/dtos/vector2/int_vector2.h
        source/game/converters/converters.h
        source/entry_point/application/application.h
        source/game/level/constants/level_maps.h
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
        source/game/game.h
        source/game/level/map/level_map.cpp
        source/game/level/map/level_map.h)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES} ${SDL2_LIBRARIES} -lmingw32 -lSDL2main -lSDL2 -lwinmm -limm32)
