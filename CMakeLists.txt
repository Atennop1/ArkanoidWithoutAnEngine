cmake_minimum_required(VERSION 3.22.1)
project(ArkanoidWithoutAnEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBS_PATH ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_PREFIX_PATH ${CMAKE_LIBS_PATH})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_executable(ArkanoidWithoutAnEngine
        src/entry_point/main.cpp
        src/entry_point/application/application.cpp
        src/entry_point/application/application.hpp
        src/game/game.cpp
        src/game/game.hpp
        src/game/rendering/window_references/window_references.cpp
        src/game/input/input.cpp
        src/game/level/constants/level_maps.cpp
        src/game/loop/game_loop.cpp
        src/game/platform/controller/platform_controller.cpp
        src/game/platform/model/platform.cpp
        src/game/platform/view/platform_view.cpp
        src/game/rendering/screen_applier.cpp
        src/game/rendering/screen_cleaner.cpp
        src/game/shortcuts/shortcuts.cpp
        src/game/level/view/level_view.cpp
        src/game/level/level.cpp
        src/game/loop/time/average_game_time.cpp
        src/game/input/input.hpp
        src/game/input/key_type.hpp
        src/game/rendering/window_references/window_references.hpp
        src/game/level/constants/level_maps.hpp
        src/game/level/view/level_view.hpp
        src/game/level/level.hpp
        src/game/loop/time/average_game_time.hpp
        src/game/loop/time/game_time.hpp
        src/game/loop/time/read_only_game_time.hpp
        src/game/loop/updatables/game_loop_events_object.hpp
        src/game/loop/updatables/game_loop_object.hpp
        src/game/loop/game_loop.hpp
        src/game/platform/controller/platform_controller.hpp
        src/game/platform/model/platform.hpp
        src/game/platform/view/platform_view.hpp
        src/game/rendering/rendering_constants.hpp
        src/game/rendering/screen_applier.hpp
        src/game/rendering/screen_cleaner.hpp
        src/game/shortcuts/render_colors.hpp
        src/game/shortcuts/shortcuts.hpp
        src/game/level/map/level_map.cpp
        src/game/level/map/level_map.hpp
        src/game/physics/physics_simulation.cpp
        src/game/physics/physics_simulation.cpp
        src/game/physics/physics_object.h
        src/game/level/constants/level_layouts.cpp
        src/game/level/constants/level_layouts.hpp
        src/tools/shared_pointer.hpp)

if(WIN32)
    set(SDL2_DIR ${CMAKE_LIBS_PATH}/SDL2/windows/lib/cmake/SDL2)
    set(SDL2_image_DIR ${CMAKE_LIBS_PATH}/SDL2_image/windows/lib/cmake/SDL2_image)
    set(Box2D ${CMAKE_LIBS_PATH}/Box2D/bin/libbox2d-d.dll)
elseif(UNIX)
    set(SDL2_DIR ${CMAKE_LIBS_PATH}/SDL2/linux/lib/cmake/SDL2)
    set(SDL2_image_DIR ${CMAKE_LIBS_PATH}/SDL2_image/linux/lib/cmake/SDL2_image)
    set(Box2D ${CMAKE_LIBS_PATH}/Box2D/bin/libbox2d.so ${CMAKE_LIBS_PATH}/Box2D/bin/libbox2d.so.2.3.2)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${_sdl2image_incdir} ${CMAKE_LIBS_PATH}/Box2D/include src/tools/)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image ${Box2D})

if(WIN32)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${SDL2_BINDIR}/SDL2.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${_sdl2image_bindir}/SDL2_image.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${Box2D} $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
endif()