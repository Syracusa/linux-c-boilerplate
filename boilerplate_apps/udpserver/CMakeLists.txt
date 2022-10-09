
file(GLOB CORE_SOURCES  ${CMAKE_SOURCE_DIR} "core/*.c")
file(GLOB CONFIG_SOURCES  ${CMAKE_SOURCE_DIR} "config/*.c")
file(GLOB UTIL_SOURCES  ${CMAKE_SOURCE_DIR} "util/*.c")

set(SOURCES ${CORE_SOURCES} 
            ${CONFIG_SOURCES} 
            ${NETUTIL_SOURCES} 
            ${UTIL_SOURCES}
            ${CONFIG_LIB_SOURCES})

add_executable(boilerplate_server ${SOURCES})

target_link_libraries(boilerplate_server PUBLIC boilerplatelib)
target_link_libraries(boilerplate_server PUBLIC iniparser)

target_include_directories(boilerplate_server PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${CMAKE_CURRENT_SOURCE_DIR}/core"
                          "${CMAKE_CURRENT_SOURCE_DIR}/config"
                          "${CMAKE_CURRENT_SOURCE_DIR}/util"
                          "${PROJECT_SOURCE_DIR}/include"
                          "${PROJECT_SOURCE_DIR}/ext/iniparser"
                          )