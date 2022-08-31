add_library(piapi piapi.c)
target_include_directories(bp PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/piapi"
                          )