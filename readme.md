# linux-c-boilerplate
+ Boilerplate code for linux c projects.
+ Include cmake build and local static library

# How to build
mkdir build
cd build
cmake ..
make

# Directory
```
apps
L ___PROJECTNAME____server : UDP server boilerplate code
L ___PROJECTNAME____testapp : Simple testapp to check library link
include : Headers
lib
L ___PROJECTNAME___ : Sample library boilerplate code 
scripts : Some useful scripts to use
ext : External librarys
L iniparser : Config parser from https://github.com/ndevilla/iniparser
```

# Todo 
+ Add shell script to easily change project name