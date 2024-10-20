cmake_minimum_required(VERSION 3.21.1)
project(ArkanoidWithoutAnEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBS_PATH ${CMAKE_SOURCE_DIR}/libs)
set(CMAKE_PREFIX_PATH ${CMAKE_LIBS_PATH})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")
add_executable(ArkanoidWithoutAnEngine ${SOURCES})

if(WIN32)
    set(SDL2_DIR ${CMAKE_LIBS_PATH}/SDL2/windows/lib/cmake/SDL2)
    set(SDL2_image_DIR ${CMAKE_LIBS_PATH}/SDL2_image/windows/lib/cmake/SDL2_image)
elseif(UNIX)
    set(SDL2_DIR ${CMAKE_LIBS_PATH}/SDL2/linux/lib/cmake/SDL2)
    set(SDL2_image_DIR ${CMAKE_LIBS_PATH}/SDL2_image/linux/lib/cmake/SDL2_image)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${_sdl2image_incdir} ${CMAKE_LIBS_PATH}/Box2D/include include/)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image ${Box2D})

if(WIN32)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${SDL2_BINDIR}/SDL2.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different  "${_sdl2image_bindir}/SDL2_image.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
endif()