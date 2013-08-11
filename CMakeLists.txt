cmake_minimum_required(VERSION 2.8.8)

project(qtpndman)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)

file (GLOB_RECURSE HEADERS include/*.h)

include_directories(include lib/libpndman/src/include)

add_subdirectory(lib)

file (GLOB_RECURSE SRCS src/*.cpp)
add_library(qtpndman ${SRCS} ${HEADERS})
target_link_libraries(qtpndman pndman)
qt5_use_modules(qtpndman Core Gui)

add_subdirectory(test)
