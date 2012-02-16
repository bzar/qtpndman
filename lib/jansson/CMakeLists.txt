PROJECT(JANSSON)

file (GLOB_RECURSE jansson_SOURCES src/src/*.c)

SET(jansson_INCLUDES
    src/src/jansson.h
    src/src/jansson_config.h)

INCLUDE_DIRECTORIES(src/src/)

FILE(COPY ${jansson_INCLUDES} DESTINATION include)
ADD_DEFINITIONS(-fPIC)
ADD_LIBRARY(jansson ${jansson_SOURCES})

