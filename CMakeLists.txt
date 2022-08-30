cmake_minimum_required(VERSION 3.10)
project(linuxcbp
        VERSION 1.0
        DESCRIPTION "Linux C Boilerplate"
        LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(lib)
add_subdirectory(apps)
add_subdirectory(ref-apps)

include(CTest)
add_subdirectory(test)
