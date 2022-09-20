mkdir -p ../winbuild
cd ../winbuild
cmake -DCMAKE_TOOLCHAIN_FILE=../TC-mingw.cmake ..
make
# make test