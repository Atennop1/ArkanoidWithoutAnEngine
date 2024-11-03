cmake_minimum_required(VERSION 3.21.1)
project(ArkanoidWithoutAnEngine)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")
add_executable(ArkanoidWithoutAnEngine ${SOURCES})

if(WIN32)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows/cmake)
    set(SDL2_IMAGE_LIB "${CMAKE_SOURCE_DIR}/libs/Genesis/windows/lib/libSDL2_image.a")
    set(ADDITIONAL_APIS setupapi user32 gdi32 winmm imm32 version)
elseif(UNIX)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux/cmake)
    set(SDL2_IMAGE_LIB "${CMAKE_SOURCE_DIR}/libs/Genesis/linux/lib/libSDL2_image.a")
endif()

set(GENESIS_SHARED_LIBS ON)
find_package(Genesis REQUIRED)

include_directories(${GENESIS_INCLUDE_DIRS} include/)
target_link_libraries(${PROJECT_NAME} PRIVATE Genesis::Genesis ${SDL2_IMAGE_LIB} ${ADDITIONAL_APIS})
