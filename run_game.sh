#!/bin/bash

# Set the library path to find finalcut
export LD_LIBRARY_PATH="/workspaces/Chinese-chess/libfinal/lib:$LD_LIBRARY_PATH"

# Set locale for Chinese characters
export LC_ALL=en_US.UTF-8

# Run the game
cd /workspaces/Chinese-chess
./build/chinese-chess "$@"
