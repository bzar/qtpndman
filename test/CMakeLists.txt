cmake_minimum_required(VERSION 2.6)

include_directories(../include)

add_executable(repository src/repository.cpp)
target_link_libraries(repository qtpndman)
