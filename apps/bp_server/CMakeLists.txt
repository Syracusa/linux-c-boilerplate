
file(GLOB CORE_SOURCES  ${CMAKE_SOURCE_DIR} "core/*.c")
file(GLOB CONFIG_SOURCES  ${CMAKE_SOURCE_DIR} "config/*.c")
file(GLOB CONFIG_LIB_SOURCES  ${CMAKE_SOURCE_DIR} "config/cfglib/*.c")
file(GLOB NETUTIL_SOURCES  ${CMAKE_SOURCE_DIR} "netutil/*.c")
file(GLOB UTIL_SOURCES  ${CMAKE_SOURCE_DIR} "util/*.c")

set(SOURCES ${CORE_SOURCES} 
            ${CONFIG_SOURCES} 
            ${NETUTIL_SOURCES} 
            ${UTIL_SOURCES}
            ${CONFIG_LIB_SOURCES})

add_executable(bpserver ${SOURCES})

target_link_libraries(bpserver PUBLIC bp)

target_include_directories(bpserver PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${CMAKE_CURRENT_SOURCE_DIR}/core"
                          "${CMAKE_CURRENT_SOURCE_DIR}/config"
                          "${CMAKE_CURRENT_SOURCE_DIR}/netutil"
                          "${CMAKE_CURRENT_SOURCE_DIR}/util"
                          "${PROJECT_SOURCE_DIR}/include"
                          )