cmake_minimum_required(VERSION 3.10)
project(linuxcbp
        VERSION 1.0
        DESCRIPTION "Linux C Boilerplate"
        LANGUAGES C)

add_subdirectory(lib)
add_subdirectory(apps)

include(CTest)
add_subdirectory(test)
