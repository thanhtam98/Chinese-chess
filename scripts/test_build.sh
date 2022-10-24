#!/bin/bash

mkdir build
cmake -S . -B build
cmake --build build
cd build && ctest