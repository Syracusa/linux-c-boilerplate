# add the executable
add_executable(mmapref mmap.c)

target_link_libraries(mmapref PUBLIC piapi)