add_executable(cmaketest2 test2.c)
target_link_libraries(cmaketest2 PUBLIC bp)
add_test(NAME cmaketest2
         COMMAND cmaketest2)