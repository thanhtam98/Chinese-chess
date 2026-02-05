# macOS Support

This document describes how to build and run Chinese Chess on macOS.

## Supported Versions

- **macOS 12 (Monterey)** or later
- **Intel (x86_64)** and **Apple Silicon (ARM64)** architectures

## Prerequisites

### Install Homebrew

If you don't have Homebrew installed:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### Install Dependencies

```bash
brew install cmake boost autoconf automake libtool pkg-config ncurses tmux
```

| Dependency | Purpose |
|------------|---------|
| cmake | Build system generator |
| boost | WebSocket (Beast), threading, regex |
| autoconf, automake, libtool | Building Finalcut library |
| pkg-config | Library discovery |
| ncurses | Terminal UI (required by Finalcut) |
| tmux | Running server/client in split panes |

## Build Instructions

### Quick Start

```bash
# Install dependencies
make deps

# Build the project (includes Finalcut library)
make setup

# Run the game
make run
```

### Step by Step

```bash
# 1. Install system dependencies
./scripts/install_deps.sh

# 2. Build Finalcut library
./scripts/build_finalcut.sh

# 3. Build the project
./scripts/build.sh

# 4. Run the game
./run_game.sh
```

### Build Options

```bash
# Debug build
make build-debug

# Release build (default)
make build-release

# Clean and rebuild
make clean-all && make setup

# Run tests
make test
```

## Running the Game

### Single Player / Local Multiplayer

```bash
make run
# or
./run_game.sh
```

### Online Multiplayer with tmux

Use tmux to run server and client in split terminal panes:

```bash
# Start tmux session with pre-configured layout
./tmux_start.sh
```

Or manually:

```bash
tmux new-session -d -s chess
tmux split-window -h
tmux send-keys -t 0 './run_game.sh' C-m   # Server window
tmux send-keys -t 1 './run_game.sh' C-m   # Client window
tmux attach-session -t chess
```

## Troubleshooting

### Characters not displaying correctly

Set the locale before running:

```bash
export LC_ALL=en_US.UTF-8
```

### Library not found error

If you see `dyld: Library not loaded` errors:

```bash
export DYLD_LIBRARY_PATH="$(pwd)/libfinal/lib:$DYLD_LIBRARY_PATH"
./build/chinese-chess
```

The `run_game.sh` script handles this automatically.

### Finalcut build fails with libtool errors

Ensure you have Homebrew's libtool (not macOS system libtool):

```bash
brew install libtool
```

The build script automatically uses `glibtoolize` on macOS.

### Boost not found

Ensure Boost is installed via Homebrew:

```bash
brew install boost
brew info boost  # Check installation path
```

### CMake can't find Boost components

This project is compatible with Boost 1.90+, which has `boost_system` as header-only. The CMakeLists.txt handles this automatically.

### ncurses header errors

If you get ncurses-related compile errors:

```bash
brew install ncurses
export PKG_CONFIG_PATH="/opt/homebrew/opt/ncurses/lib/pkgconfig:$PKG_CONFIG_PATH"
```

## Technical Notes

### Boost.Beast WebSocket

This project uses Boost.Beast for WebSocket communication instead of WebSocket++. Beast is part of Boost and provides native compatibility with modern Boost versions (1.87+).

### Library Extensions

- Linux: `.so` (shared object)
- macOS: `.dylib` (dynamic library)

The build system handles this automatically.

### Vendored Dependencies

The following are vendored in `third_party/` for offline builds:

- **GoogleTest** 1.12.1 - Unit testing
- **nlohmann/json** 3.11.2 - JSON parsing  
- **Finalcut** 0.9.1 - Terminal UI library

No network access required after initial repository clone.

## Directory Structure (After Build)

```
Chinese-chess/
├── third_party/          # Vendored dependencies
│   ├── googletest/
│   ├── json/
│   └── finalcut/
├── build/                # Build output
│   └── chinese-chess     # Main executable
├── libfinal/             # Installed Finalcut library
│   ├── include/
│   └── lib/
│       └── libfinal.dylib
└── final/                # Finalcut headers (symlink)
```
