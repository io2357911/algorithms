cmake_minimum_required(VERSION 2.8)


# project params


set(PROJ_NAME test)

project(${PROJ_NAME})

add_definitions(-Wall -std=c++11)


# sources and includes


include_directories(../include)

set(SOURCES
    src/main.cpp
    src/test.cpp
)


# create executable


add_executable(${PROJ_NAME} ${SOURCES})
add_test(${PROJ_NAME} ${PROJ_NAME})

target_link_libraries(${PROJ_NAME} 
    cppunit
    pthread
)
