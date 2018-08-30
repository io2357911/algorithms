cmake_minimum_required(VERSION 2.8)


# params


add_definitions(-Wall -fno-strict-aliasing)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Os" CACHE STRING "" FORCE)


# target


set(TARGET "pc" CACHE STRING "target platform arm|pc")

if (${TARGET} STREQUAL "arm")
	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toolchain.txt)
endif()


# build type


set(BUILD "release" CACHE STRING "build type debug|release")

if (${BUILD} STREQUAL "release")
	SET(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
elseif (${BUILD} STREQUAL "debug")
	SET(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()


# project


project(algorithms)

add_subdirectory(test)

if (${TARGET} STREQUAL "pc")
endif()

