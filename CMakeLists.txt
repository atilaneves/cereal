cmake_minimum_required(VERSION 2.8)

project(cereal)

find_package(Boost COMPONENTS system program_options REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

#set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: Debug Release"
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(GRAV_FLAGS_DEBUG "-Wall -Wextra -Werror -g -pg -fno-inline")
set(GRAV_FLAGS_RELEASE "-Wall -Wextra -Werror  -O2")

set(CMAKE_C_FLAGS_DEBUG ${GRAV_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_DEBUG "${GRAV_FLAGS_DEBUG} -std=c++11")

set(CMAKE_C_FLAGS_RELEASE ${GRAV_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_RELEASE "${GRAV_FLAGS_RELEASE} -std=c++11")

message("Build type is ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message("Release C   flags are ${CMAKE_C_FLAGS_RELEASE}")
  message("Release C++ flags are ${CMAKE_CXX_FLAGS_RELEASE}")
else()
  message("Debug   C   flags are ${CMAKE_C_FLAGS_DEBUG}")
  message("Debug   C++ flags are ${CMAKE_CXX_FLAGS_DEBUG}")
endif()


include_directories(${CMAKE_SOURCE_DIR}/unit-thread/lib)
include_directories(src)

FILE(GLOB UNIT_THREAD_SRCS ${CMAKE_SOURCE_DIR}/unit-thread/lib/*.cpp)
FILE(GLOB CEREAL_SRCS src/*.cpp)
FILE(GLOB TEST_SRCS test/*.cpp)

add_library(unit_thread ${UNIT_THREAD_SRCS})
add_executable(test ${CEREAL_SRCS}
                    ${TEST_SRCS}
                    ${CMAKE_SOURCE_DIR}/unit-thread/sample/test_main.cpp)

if(WIN32 AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
endif()


target_link_libraries(test unit_thread ${Boost_LIBRARIES})

if(WIN32)
else()
    target_link_libraries(test pthread)
endif()
