# add the executable
add_executable(tcpref tcpref.c)

target_link_libraries(tcpref PUBLIC piapi)