cmake_minimum_required(VERSION 2.8.8)

project(qtpndman)

option(QTPNDMAN_NO_SYSTEM_LIBS "Force build depencies from git" OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)

if (NOT QTPNDMAN_NO_SYSTEM_LIBS)
    find_library(PNDMAN_LIBRARY pndman)
endif ()

if (PNDMAN_LIBRARY)
    list(APPEND QTPNDMAN_LINK ${PNDMAN_LIBRARY})
endif ()

# Export qtpndman library dependencies
SET(QTPNDMAN_LIBRARIES ${QTPNDMAN_LINK} CACHE STRING "Dependencies of qtpndman")

file (GLOB_RECURSE HEADERS include/*.h)

add_subdirectory(lib)
include_directories(include ${QTPNDMAN_STATIC_INCL})

file (GLOB_RECURSE SRCS src/*.cpp)
add_library(qtpndman ${SRCS} ${HEADERS})
target_link_libraries(qtpndman ${QTPNDMAN_LIBRARIES} ${QTPNDMAN_STATIC_LINK} ${LIBPNDMAN_LIBRARIES})
qt5_use_modules(qtpndman Core Gui)

add_subdirectory(test)
