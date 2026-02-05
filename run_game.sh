#!/bin/bash

# Get the script's directory (project root)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Set the library path to find finalcut (platform-specific)
if [[ "$OSTYPE" == "darwin"* ]]; then
    export DYLD_LIBRARY_PATH="$SCRIPT_DIR/libfinal/lib:$DYLD_LIBRARY_PATH"
else
    export LD_LIBRARY_PATH="$SCRIPT_DIR/libfinal/lib:$LD_LIBRARY_PATH"
fi

# Set locale for Chinese characters
export LC_ALL=en_US.UTF-8

# Run the game
./build/chinese-chess "$@"
