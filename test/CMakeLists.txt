cmake_minimum_required(VERSION 2.6)

include_directories(../include)

file (GLOB_RECURSE TEST_HEADERS src/*.h)
QT4_WRAP_CPP(TEST_SRC_MOC ${TEST_HEADERS})

add_executable(repository src/repository.cpp src/moc_repository.cxx)
target_link_libraries(repository qtpndman)

add_executable(device src/device.cpp src/moc_device.cxx)
target_link_libraries(device qtpndman)
