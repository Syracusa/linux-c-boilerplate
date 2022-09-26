add_executable(cmaketest2 test2.c)
target_link_libraries(cmaketest2 PUBLIC ___PROJECTNAME___)
add_test(NAME cmaketest2
         COMMAND cmaketest2)