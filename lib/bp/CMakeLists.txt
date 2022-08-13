add_library(bp bp.c)

target_include_directories(bp PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/bp"
                          )