#!/bin/bash

mkdir build
echo $(pwd)
cmake -S . -B build
cmake --build build
cd build && ctest