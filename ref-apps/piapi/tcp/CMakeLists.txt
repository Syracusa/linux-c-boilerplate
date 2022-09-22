# add the executable
add_executable(tcptest tcptest.c)

target_link_libraries(tcptest PUBLIC piapi)