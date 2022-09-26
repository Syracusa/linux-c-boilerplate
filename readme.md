# Linux-C-Boilerplate
+ Boilerplate code for linux c projects.
+ Include cmake build and local static library
+ Include platfrom-independent API Lib(PIAPI)

# How to build
mkdir build
cd build
cmake ..
make

# Directory
```
apps
L bp_server : UDP server boilerplate code
L testapp : Simple testapp to check library link
include : Headers
lib
L bp : Sample library boilerplate code 
scripts : Some useful scripts to use
L ref-apps : PIAPI lib sample program
```

# Todo 
+ Add shell script to easily change project name