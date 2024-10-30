cmake_minimum_required(VERSION 3.21.1)
project(ArkanoidWithoutAnEngine)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")
add_executable(ArkanoidWithoutAnEngine ${SOURCES})

if(WIN32)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows/cmake)
elseif(UNIX)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux/cmake)
endif()

find_package(Genesis REQUIRED)
include_directories(${GENESIS_INCLUDE_DIRS} include/)
target_link_libraries(${PROJECT_NAME} Genesis::Genesis)

if(WIN32)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/libs/Genesis/windows/lib/SDL2.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/libs/Genesis/windows/lib/SDL2_image.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
    add_custom_command(TARGET ArkanoidWithoutAnEngine POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/libs/Genesis/windows/lib/Genesis.dll" $<TARGET_FILE_DIR:ArkanoidWithoutAnEngine>)
endif()