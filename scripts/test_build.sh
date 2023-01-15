#!/bin/bash

mkdir build
echo $(pwd)
ls
#cat CmakeLists.txt
cmake -S . -B build
cmake --build build
cd build && ctest $1 
