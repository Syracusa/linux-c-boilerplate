# add the executable
add_executable(testapp main.c)

target_link_libraries(testapp PUBLIC ___PROJECTNAME___)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(testapp PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include"
                          )