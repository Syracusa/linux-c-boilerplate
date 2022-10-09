cmake_minimum_required(VERSION 3.10)
project(linux-c-boilerplate
        VERSION 1.0
        DESCRIPTION "Linux c boilerplate code"
        LANGUAGES C)
              
## Disable this when publish
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")

add_subdirectory(ext)
add_subdirectory(lib)
add_subdirectory(boilerplate_apps)