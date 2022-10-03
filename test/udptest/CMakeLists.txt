add_executable(udptest udptest.c)

target_link_libraries(udptest PUBLIC piapi)

add_test(NAME udptest
         COMMAND udptest)

         