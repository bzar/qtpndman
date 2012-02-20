cmake_minimum_required(VERSION 2.6)

include_directories(../include)

file (GLOB_RECURSE TEST_HEADERS src/*.h)
QT4_WRAP_CPP(TEST_SRC_MOC ${TEST_HEADERS})

add_executable(repositorytest src/repositorytest.cpp src/moc_repositorytest.cxx)
target_link_libraries(repositorytest qtpndman)

add_executable(devicetest src/devicetest.cpp src/moc_devicetest.cxx)
target_link_libraries(devicetest qtpndman)

add_executable(packageinfotest src/packageinfotest.cpp src/moc_packageinfotest.cxx)
target_link_libraries(packageinfotest qtpndman)

add_executable(downloadtest src/downloadtest.cpp)
target_link_libraries(downloadtest qtpndman)