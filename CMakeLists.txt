cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(CMAKE_CXX_FLAGS "-g -Wall")
#set(CMAKE_CXX_FLAGS "-Wall")

file (GLOB_RECURSE HEADERS include/*.h)
QT4_WRAP_CPP(SRC_MOC ${HEADERS})

include_directories(include lib/libpndman/src/include)

add_subdirectory(lib)

file (GLOB_RECURSE SRCS src/*.cpp)
add_library(qtpndman ${SRCS} ${SRC_MOC} ${HEADERS})
target_link_libraries(qtpndman ${QT_LIBRARIES} pndman)

add_subdirectory(test)
