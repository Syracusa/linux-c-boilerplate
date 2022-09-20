# add the executable
add_executable(timertest main.c)

find_library(LIBRT rt) 
if(LIBRT)
   target_link_libraries(timertest ${LIBRT})
endif()

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(timertest PUBLIC "-pthread")
endif()
