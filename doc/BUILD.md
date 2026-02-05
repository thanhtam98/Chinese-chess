# Chinese Chess - Build System Documentation

## Overview

This document describes the refactored build system for the Chinese Chess project. The build system has been completely redesigned to be more robust, user-friendly, and maintainable.

## Quick Start

### 1. Install Dependencies
```bash
make deps
# or
./scripts/install_deps.sh
```

### 2. Build the Project
```bash
make build
# or
./scripts/build.sh
```

### 3. Run the Game
```bash
make run
# or
./run_game.sh
```

### 4. Run Tests
```bash
make test
# or
./scripts/run_tests.sh
```

## Build System Architecture

### Components

1. **CMakeLists.txt** - Main build configuration
2. **Makefile** - High-level project management
3. **Scripts/** - Detailed build and utility scripts
4. **run_game.sh** - Game launcher with proper environment setup

### Directory Structure

```
Chinese-chess/
├── CMakeLists.txt          # Main CMake configuration
├── Makefile                # Project management
├── run_game.sh             # Game launcher
├── tmux_start.sh           # tmux session launcher
├── doc/                    # Documentation
│   └── BUILD.md            # This documentation
├── scripts/                # Build scripts
│   ├── build.sh            # Main build script
│   ├── build_finalcut.sh   # Finalcut library builder
│   ├── install_deps.sh     # Dependency installer
│   └── run_tests.sh        # Test runner
├── third_party/            # Vendored dependencies (offline build)
│   ├── googletest/         # GoogleTest 1.12.1
│   ├── json/               # nlohmann/json 3.11.2
│   └── finalcut/           # Finalcut 0.9.1 source
├── build/                  # Build output directory (generated)
├── libfinal/               # Finalcut library installation (generated)
└── final/                  # Finalcut headers (generated)
```

## Build Scripts

### Main Build Script (`scripts/build.sh`)

The main build script provides comprehensive build management with the following features:

**Usage:**
```bash
./scripts/build.sh [OPTIONS]
```

**Options:**
- `-t, --type TYPE` - Build type (Debug|Release) [default: Release]
- `-c, --clean` - Clean build directory before building
- `-f, --rebuild-finalcut` - Rebuild finalcut library from scratch
- `-j, --jobs N` - Number of parallel jobs [default: $(nproc)]
- `-v, --verbose` - Verbose output
- `--test` - Run tests after building
- `-h, --help` - Show help message

**Examples:**
```bash
# Basic build
./scripts/build.sh

# Debug build with clean
./scripts/build.sh -t Debug -c

# Rebuild finalcut and run tests
./scripts/build.sh -f --test

# Verbose build with custom job count
./scripts/build.sh -v -j 4
```

### Dependency Installer (`scripts/install_deps.sh`)

Automatically installs system dependencies for different operating systems.

**Supported Systems:**
- macOS (Homebrew)
- Ubuntu/Debian (apt-get)
- CentOS/RHEL (yum)
- Arch Linux (pacman)

**Usage:**
```bash
./scripts/install_deps.sh
# or
make deps
```

**macOS Manual Installation:**
```bash
brew install cmake boost autoconf automake libtool pkg-config ncurses tmux
```

**Ubuntu/Debian Manual Installation:**
```bash
sudo apt-get install build-essential cmake git pkg-config \
    autoconf automake libtool libboost-all-dev \
    libncurses-dev libtinfo-dev tmux
```

### Finalcut Builder (`scripts/build_finalcut.sh`)

Builds the finalcut library with proper configuration and error handling.

**Features:**
- Uses vendored source from `third_party/finalcut/` (offline build)
- Falls back to GitHub clone if vendored source not available
- Cross-platform support (Linux and macOS)
- Automatic dependency checking
- Version management (currently 0.9.1)
- Clean build support
- Parallel compilation
- Installation verification

**macOS Notes:**
- Uses `glibtoolize` instead of `libtoolize`
- Produces `.dylib` instead of `.so` library files

### Test Runner (`scripts/run_tests.sh`)

Comprehensive test runner with filtering and verbose output support.

**Usage:**
```bash
./scripts/run_tests.sh [OPTIONS]
```

**Options:**
- `-f, --filter PATTERN` - Run only tests matching PATTERN
- `-v, --verbose` - Verbose output
- `-b, --build-dir DIR` - Build directory [default: build]
- `-h, --help` - Show help message

**Examples:**
```bash
# Run all tests
./scripts/run_tests.sh

# Run specific test
./scripts/run_tests.sh -f PointTest

# Verbose output
./scripts/run_tests.sh -v
```

## Makefile Targets

The Makefile provides high-level project management with the following targets:

### Build Targets
- `make build` - Build the project (default)
- `make build-debug` - Build in Debug mode
- `make build-release` - Build in Release mode
- `make clean` - Clean build directory
- `make clean-all` - Clean all build artifacts and dependencies

### Dependency Targets
- `make deps` - Install system dependencies
- `make finalcut` - Build finalcut library
- `make rebuild-finalcut` - Rebuild finalcut library from scratch

### Test Targets
- `make test` - Run all tests
- `make test-verbose` - Run tests with verbose output
- `make test-filter FILTER=TestName` - Run tests matching FILTER

### Run Targets
- `make run` - Run the game
- `make run-debug` - Run the game in debug mode

### Development Targets
- `make setup` - Complete project setup (deps + build)
- `make rebuild` - Clean and rebuild everything
- `make status` - Show project status

### Variables
- `BUILD_TYPE` - Build type (Debug|Release) [default: Release]
- `JOBS` - Number of parallel jobs [default: $(nproc)]
- `VERBOSE` - Verbose output (true|false) [default: false]

## CMake Configuration

The CMakeLists.txt has been completely refactored with the following improvements:

### Features
- **Modular Structure** - Clear separation of concerns
- **Dependency Management** - Automatic handling of external dependencies
- **Build Type Support** - Debug and Release configurations
- **RPATH Configuration** - Proper runtime library linking
- **Test Integration** - GoogleTest integration with CTest
- **Installation Support** - Proper installation targets

### External Dependencies

**Vendored in `third_party/` (offline build support):**
- **GoogleTest** 1.12.1 - Testing framework
- **nlohmann/json** 3.11.2 - JSON library
- **Finalcut** 0.9.1 - Terminal UI library (built with autotools)

**System dependencies:**
- **Boost** (1.66+) - System, thread, regex, and Beast (WebSocket) libraries
- **ncurses** - Terminal handling (required by Finalcut)
- **tmux** - Terminal multiplexer (for running server/client)

## Error Handling and Validation

### Dependency Checking
All scripts include comprehensive dependency checking:
- System tools (cmake, g++, git, etc.)
- Library dependencies (Boost, etc.)
- Build artifacts verification

### Error Reporting
- Colored output for better visibility
- Clear error messages with suggested solutions
- Exit codes for proper error handling
- Verbose mode for debugging

### Validation
- Build artifact verification
- Library linking validation
- Test execution verification

## Environment Setup

### Runtime Environment
The `run_game.sh` script sets up the proper environment for the current platform:

**Linux:**
```bash
export LD_LIBRARY_PATH="$(pwd)/libfinal/lib:$LD_LIBRARY_PATH"
export LC_ALL=en_US.UTF-8
./build/chinese-chess "$@"
```

**macOS:**
```bash
export DYLD_LIBRARY_PATH="$(pwd)/libfinal/lib:$DYLD_LIBRARY_PATH"
export LC_ALL=en_US.UTF-8
./build/chinese-chess "$@"
```

### Build Environment
- Automatic compiler detection
- Parallel build support
- Proper include paths
- Library linking configuration

## Troubleshooting

### Common Issues

1. **Missing Dependencies**
   ```bash
   make deps
   ```

2. **Finalcut Library Issues**
   ```bash
   make rebuild-finalcut
   ```

3. **Build Failures**
   ```bash
   make clean-all
   make setup
   ```

4. **Runtime Library Errors**
   ```bash
   ./run_game.sh  # Uses proper environment setup
   ```

### Debug Mode
For debugging issues:
```bash
make build-debug
make run-debug
```

### Verbose Output
For detailed build information:
```bash
./scripts/build.sh -v
make test-verbose
```

## Performance Optimization

### Build Performance
- Parallel compilation (uses all CPU cores by default)
- Incremental builds (only rebuilds changed files)
- Dependency caching

### Runtime Performance
- Release build optimizations (-O3)
- Proper library linking
- Memory management

## Maintenance

### Updating Dependencies
To update external dependencies, modify the FetchContent declarations in CMakeLists.txt.

### Adding New Features
1. Add source files to the appropriate GLOB in CMakeLists.txt
2. Update include directories if needed
3. Add tests to the test directory
4. Update documentation

### Version Management
- Project version in CMakeLists.txt
- Finalcut version in build_finalcut.sh
- Dependency versions in FetchContent declarations

## Best Practices

1. **Always use the provided scripts** instead of direct cmake commands
2. **Run tests after building** to ensure everything works
3. **Use clean builds** when encountering issues
4. **Check dependencies** before building
5. **Use verbose mode** for debugging

## Platform Support

### Supported Platforms
- ✅ **Linux** (Ubuntu 20.04+, Debian, CentOS 8+, Arch Linux)
- ✅ **macOS** (macOS 12+ with Homebrew, Intel and Apple Silicon)

### macOS Specifics
- Uses Homebrew for dependency management
- Finalcut builds with `glibtoolize` (Homebrew's libtool)
- Library extension: `.dylib` instead of `.so`
- Works with Boost 1.90+ (uses Boost.Beast for WebSocket)

### Offline Build Support
All dependencies are vendored in `third_party/`:
```
third_party/
├── googletest/    # GoogleTest 1.12.1
├── json/          # nlohmann/json 3.11.2
└── finalcut/      # Finalcut 0.9.1
```

No network access required after initial repository clone.

## Future Improvements

Potential enhancements for the build system:
- Docker support for consistent environments
- CI/CD integration
- Package management integration
- Automated testing in different environments
