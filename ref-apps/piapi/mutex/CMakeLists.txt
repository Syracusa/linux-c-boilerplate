# add the executable
add_executable(mref mutex.c)

target_link_libraries(mref PUBLIC piapi)