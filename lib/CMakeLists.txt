add_library(___PROJECTNAME___ ___PROJECTNAME___.c)

target_include_directories(___PROJECTNAME___ PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/___PROJECTNAME___"
                          )