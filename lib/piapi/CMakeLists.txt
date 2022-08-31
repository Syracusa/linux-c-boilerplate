add_library(piapi piapi.c pi_sock.c pi_mmap.c pi_thread.c)
target_include_directories(piapi PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include/piapi/"
                          "${PROJECT_SOURCE_DIR}/lib/piapi/"
                          )
                          
if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    target_link_libraries(piapi ws2_32 kernel32)
endif()