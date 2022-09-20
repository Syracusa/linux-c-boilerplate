# add the executable
add_executable(client client.c)
target_link_libraries(client PUBLIC piapi)

add_executable(server server.c)
target_link_libraries(server PUBLIC piapi)
