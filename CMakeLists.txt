cmake_minimum_required(VERSION 3.21.1)
project(ArkanoidWithoutAnEngine)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")
add_executable(ArkanoidWithoutAnEngine ${SOURCES})

if(WIN32)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows/cmake)
    set(GENESIS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows)
    set(ADDITIONAL_APIS setupapi user32 gdi32 winmm imm32 version)
    set(CMAKE_EXE_LINKER_FLAGS "-static -mwindows")

    set(SDL2_IMAGE_LIB "${CMAKE_SOURCE_DIR}/libs/SDL2_image/windows/lib/libSDL2_image.a")
    set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2_image/windows/include")
elseif(UNIX)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux/cmake)
    set(GENESIS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux)

    set(SDL2_IMAGE_LIB "${CMAKE_SOURCE_DIR}/libs/SDL2_image/linux/lib/libSDL2_image.a")
    set(SDL2_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2_image/linux/include")
endif()

set(GENESIS_SHARED_LIBS OFF)
find_package(Genesis REQUIRED)

include_directories(${GENESIS_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} include)
target_link_libraries(${PROJECT_NAME} PRIVATE Genesis::Genesis ${SDL2_IMAGE_LIB} ${ADDITIONAL_APIS})
