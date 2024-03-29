cmake_minimum_required(VERSION 3.22.1)
project(ArkanoidWithoutAnEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBS_PATH ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_PREFIX_PATH ${CMAKE_LIBS_PATH})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

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

if(WIN32)
    set(SDL2_DIR ${CMAKE_LIBS_PATH}/SDL2/windows/lib/cmake/SDL2)
    set(SDL2_image_DIR ${CMAKE_LIBS_PATH}/SDL2_image/windows/lib/cmake/SDL2_image)
elseif(UNIX)
    set(SDL2_DIR ${CMAKE_LIBS_PATH}/SDL2/linux/lib/cmake/SDL2)
    set(SDL2_image_DIR ${CMAKE_LIBS_PATH}/SDL2_image/linux/lib/cmake/SDL2_image)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${_sdl2image_incdir})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image)

if(WIN32)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${SDL2_BINDIR}/SDL2.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${_sdl2image_bindir}/SDL2_image.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
endif()