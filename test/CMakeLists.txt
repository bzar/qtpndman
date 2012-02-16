cmake_minimum_required(VERSION 2.6)

include_directories(../include)

add_executable(repository src/repository.cpp)
target_link_libraries(repository qtpndman)

add_executable(device src/device.cpp)
target_link_libraries(device qtpndman)
