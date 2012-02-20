cmake_minimum_required(VERSION 2.6)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${JANSSON_BINARY_DIR}/include/)
set(CMAKE_CXX_FLAGS "-g -Wall")
file (GLOB_RECURSE PNDMAN_SRCS src/lib/*.c)
add_library(pndman ${PNDMAN_SRCS})
target_link_libraries(pndman curl ssl jansson crypto expat)
