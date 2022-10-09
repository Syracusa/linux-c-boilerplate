add_library(boilerplatelib boilerplatelib.c)

target_include_directories(boilerplatelib PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/"
                          ) 