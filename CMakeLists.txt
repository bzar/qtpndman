cmake_minimum_required(VERSION 2.6)

project(qtpndman)

option(QTPNDMAN_NO_SYSTEM_LIBS "Force build depencies from git" OFF)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
ADD_DEFINITIONS(-fPIC)

if (NOT QTPNDMAN_NO_SYSTEM_LIBS)
    find_library(PNDMAN_LIBRARY pndman)
endif ()

if (PNDMAN_LIBRARY)
    list(APPEND QTPNDMAN_LINK ${PNDMAN_LIBRARY})
endif ()

file (GLOB_RECURSE HEADERS include/*.h)
QT4_WRAP_CPP(SRC_MOC ${HEADERS})

# Export qtpndman library dependencies
SET(QTPNDMAN_LIBRARIES ${QTPNDMAN_LINK} CACHE STRING "Dependencies of qtpndman")

file (GLOB_RECURSE HEADERS include/*.h)

add_subdirectory(lib)
include_directories(include ${QTPNDMAN_STATIC_INCL})

file (GLOB_RECURSE SRCS src/*.cpp)
add_library(qtpndman ${SRCS} ${SRC_MOC} ${HEADERS})
target_link_libraries(qtpndman ${QT_LIBRARIES} ${QTPNDMAN_LIBRARIES} ${QTPNDMAN_STATIC_LINK} ${LIBPNDMAN_LIBRARIES})

add_subdirectory(test)
