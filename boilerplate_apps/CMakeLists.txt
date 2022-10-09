add_subdirectory(udpserver)

add_executable(linktest linktest/linktest.c)

target_link_libraries(linktest boilerplatelib)
target_include_directories(linktest PUBLIC "${PROJECT_SOURCE_DIR}/include")