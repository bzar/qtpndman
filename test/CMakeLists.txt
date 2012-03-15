cmake_minimum_required(VERSION 2.6)

include_directories(../include)

add_executable(repositorytest src/repositorytest.cpp)
target_link_libraries(repositorytest qtpndman)

add_executable(devicetest src/devicetest.cpp)
target_link_libraries(devicetest qtpndman)

add_executable(packageinfotest src/packageinfotest.cpp)
target_link_libraries(packageinfotest qtpndman)

add_executable(downloadtest src/downloadtest.cpp)
target_link_libraries(downloadtest qtpndman)

add_executable(upgradetest src/upgradetest.cpp)
target_link_libraries(upgradetest qtpndman)

add_executable(removetest src/removetest.cpp)
target_link_libraries(removetest qtpndman)
