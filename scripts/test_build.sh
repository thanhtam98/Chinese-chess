#!/bin/bash

mkdir build
echo $(pwd)
ls
cat CmakeLists.txt
cmake -S /builds/oop-programming/chinese-chess -B build
cmake --build build
cd build && ctest