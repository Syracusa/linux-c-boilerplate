# linux-c-boilerplate
+ Boilerplate code for linux c projects.
+ Include cmake build 
+ Local static library build/link example

# How to build
```
mkdir build
cd build
cmake ..
make
```

# Execute test applications
## boilerplate_server
+ Udp server/client implementation boilerplate code
+ Include Select() example
```
cd scripts/boilerplate_server

# Server
./server_exe.sh

# Client
./client.exe.sh
```
+ Modify /scripts/boilerplate_server/server.cfg(or client.cfg) to change port/ip

## linktest
+ Test local library link

## mmap
+ Memory-mapped file example(TBD)

# Directory
```
apps
L boilerplate_server : UDP server boilerplate code
L boilerplate_testapp : Simple testapp to check library link
include : Headers
lib
L Sample library boilerplate code 
scripts : Some useful scripts to use
ext : External librarys
L iniparser : Config parser from https://github.com/ndevilla/iniparser
```

# Todo 
