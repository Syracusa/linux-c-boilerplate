# add the executable
add_executable(tref thread.c)

target_link_libraries(tref PUBLIC piapi)