add_executable(udptest test1.c)

target_link_libraries(udptest PUBLIC piapi)

add_test(NAME udptest
         COMMAND udptest)

         