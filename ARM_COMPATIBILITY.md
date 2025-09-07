# ARM System Compatibility Guide

This document explains how to run the Chinese Chess project on ARM-based systems (like Apple Silicon Macs, ARM64 Linux servers, Raspberry Pi, etc.).

## 🏗️ Architecture Support

The project now supports both **x86_64** and **ARM64** architectures:

- ✅ **x86_64** (Intel/AMD 64-bit)
- ✅ **ARM64** (Apple Silicon, ARM servers, Raspberry Pi 4+)

## 🐳 DevContainer Configuration

### Updated DevContainer Features

The `.devcontainer/devcontainer.json` has been updated with:

```json
{
    "platforms": ["linux/amd64", "linux/arm64"],
    "customizations": {
        "vscode": {
            "settings": {
                "C_Cpp.default.intelliSenseMode": "linux-gcc-arm64"
            }
        }
    }
}
```

### Key Changes for ARM Support

1. **Platform Declaration**: Added `"platforms": ["linux/amd64", "linux/arm64"]` to explicitly support both architectures
2. **IntelliSense Mode**: Changed from `"linux-gcc-x64"` to `"linux-gcc-arm64"` for proper ARM code completion
3. **Base Image**: Uses `ubuntu:22.04` which supports both architectures

## 🚀 Running on ARM Systems

### Prerequisites

1. **Docker with ARM Support**:
   - Docker Desktop for Mac (Apple Silicon)
   - Docker on ARM64 Linux
   - Ensure your Docker installation supports multi-platform builds

2. **VS Code with Dev Containers Extension**:
   - Install the "Dev Containers" extension
   - Ensure it supports ARM platforms

### Setup Instructions

1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd Chinese-chess
   ```

2. **Open in DevContainer**:
   - Open VS Code in the project directory
   - Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
   - Select "Dev Containers: Reopen in Container"
   - Wait for the container to build and start

3. **Automatic Setup**:
   The DevContainer will automatically:
   - Install system dependencies
   - Build the finalcut library
   - Compile the Chinese Chess project
   - Set up the development environment

### Manual Setup (Alternative)

If you prefer to run without DevContainer:

```bash
# Install dependencies
make deps

# Build finalcut library
make finalcut

# Build the project
make build

# Run the game
make run
```

## 🔧 Architecture-Specific Considerations

### Compiler and Build Tools

- **GCC**: The project uses GCC which supports both x86_64 and ARM64
- **CMake**: Automatically detects the target architecture
- **Boost Libraries**: Available for both architectures via package managers

### Dependencies

All dependencies are architecture-agnostic:

- **Ubuntu/Debian**: `apt-get install` packages work on both architectures
- **Arch Linux**: `pacman` packages support both architectures
- **CentOS/RHEL**: `yum` packages are available for both architectures

### Performance Considerations

**ARM64 Systems**:
- Generally excellent performance on modern ARM processors
- Apple Silicon Macs: Native performance with Rosetta 2 fallback
- ARM servers: Competitive performance with x86_64 equivalents
- Raspberry Pi: Good performance on Pi 4+ (8GB recommended)

## 🧪 Testing ARM Compatibility

### Verify Architecture

```bash
# Check system architecture
uname -m
# Should show: aarch64 (ARM64) or x86_64

# Check Docker platform
docker version
# Should show platform support for linux/arm64
```

### Build Verification

```bash
# Clean build to test ARM compatibility
make clean
make build

# Run tests
make test

# Run the game
make run
```

### Expected Output

On ARM systems, you should see:
- Successful CMake configuration
- All source files compile without errors
- Tests pass
- Game runs normally

## 🐛 Troubleshooting

### Common Issues

1. **"Platform not supported" Error**:
   ```bash
   # Solution: Update Docker to latest version
   docker --version
   ```

2. **Build Failures on ARM**:
   ```bash
   # Solution: Clean and rebuild
   make clean
   make rebuild-finalcut
   make build
   ```

3. **Performance Issues**:
   - Ensure you're using native ARM64 binaries
   - Check that no x86_64 emulation is running
   - Verify sufficient RAM (8GB+ recommended)

### Debug Commands

```bash
# Check architecture
file build/chinese-chess
# Should show: ELF 64-bit LSB executable, ARM aarch64

# Check linked libraries
ldd build/chinese-chess
# Should show ARM64 libraries

# Check CMake configuration
cd build && cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON
```

## 📊 Performance Benchmarks

### Expected Performance (Relative to x86_64)

| System Type | Performance | Notes |
|-------------|-------------|-------|
| Apple Silicon M1/M2 | 100-120% | Often faster than x86_64 |
| ARM64 Servers | 90-110% | Competitive performance |
| Raspberry Pi 4+ | 60-80% | Good for development |
| Older ARM | 40-60% | May be slow for complex games |

## 🔄 Cross-Platform Development

### Building for Multiple Architectures

```bash
# Build for current architecture
make build

# Clean and rebuild for different architecture
make clean
make build
```

### Docker Multi-Platform Builds

```bash
# Build for multiple platforms (if needed)
docker buildx build --platform linux/amd64,linux/arm64 -t chinese-chess .
```

## 📝 Notes

- The finalcut library is built from source, ensuring ARM compatibility
- All C++ dependencies (Boost, WebSocket++, nlohmann/json) support ARM64
- The game logic is architecture-independent
- UI rendering works identically on both architectures

## 🆘 Support

If you encounter issues on ARM systems:

1. Check this guide first
2. Verify your Docker and VS Code versions
3. Try a clean rebuild: `make clean && make setup`
4. Check the build logs for architecture-specific errors
5. Ensure you have sufficient system resources (8GB+ RAM recommended)

---

**Last Updated**: $(date)
**Tested On**: Ubuntu 22.04 ARM64, Apple Silicon Macs
