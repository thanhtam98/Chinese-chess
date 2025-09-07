#!/bin/bash

# =============================================================================
# Chinese Chess Build Script
# =============================================================================

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Default values
BUILD_TYPE="Release"
CLEAN=false
REBUILD_FINALCUT=false
RUN_TESTS=false
VERBOSE=false
JOBS=$(nproc)

# =============================================================================
# Functions
# =============================================================================

print_usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -t, --type TYPE        Build type (Debug|Release) [default: Release]"
    echo "  -c, --clean           Clean build directory before building"
    echo "  -f, --rebuild-finalcut Rebuild finalcut library from scratch"
    echo "  -j, --jobs N           Number of parallel jobs [default: $(nproc)]"
    echo "  -v, --verbose          Verbose output"
    echo "  --test                 Run tests after building"
    echo "  -h, --help             Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                     # Build in Release mode"
    echo "  $0 -t Debug -c         # Clean build in Debug mode"
    echo "  $0 -f --test           # Rebuild finalcut and run tests"
}

log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

check_dependencies() {
    log_info "Checking system dependencies..."
    
    local missing_deps=()
    
    # Check for required tools
    command -v cmake >/dev/null 2>&1 || missing_deps+=("cmake")
    command -v g++ >/dev/null 2>&1 || missing_deps+=("g++")
    command -v git >/dev/null 2>&1 || missing_deps+=("git")
    command -v pkg-config >/dev/null 2>&1 || missing_deps+=("pkg-config")
    
    # Check for Boost (try different methods)
    if ! pkg-config --exists libboost-system 2>/dev/null && ! ldconfig -p | grep -q libboost_system; then
        missing_deps+=("libboost-dev")
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        log_error "Missing dependencies: ${missing_deps[*]}"
        log_info "Install them with: sudo apt-get install ${missing_deps[*]}"
        exit 1
    fi
    
    log_success "All dependencies found"
}

clean_build() {
    log_info "Cleaning build directory..."
    if [ -d "$PROJECT_ROOT/build" ]; then
        rm -rf "$PROJECT_ROOT/build"
        log_success "Build directory cleaned"
    else
        log_info "No build directory to clean"
    fi
}

rebuild_finalcut() {
    log_info "Rebuilding finalcut library..."
    cd "$PROJECT_ROOT"
    ./scripts/build_finalcut.sh
    log_success "Finalcut library rebuilt"
}

configure_cmake() {
    log_info "Configuring CMake..."
    cd "$PROJECT_ROOT"
    
    local cmake_args=(
        "-S" "."
        "-B" "build"
        "-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
    )
    
    if [ "$VERBOSE" = true ]; then
        cmake_args+=("-DCMAKE_VERBOSE_MAKEFILE=ON")
    fi
    
    if ! cmake "${cmake_args[@]}"; then
        log_error "CMake configuration failed"
        exit 1
    fi
    
    log_success "CMake configured successfully"
}

build_project() {
    log_info "Building project..."
    cd "$PROJECT_ROOT"
    
    local build_args=("--build" "build")
    
    if [ "$VERBOSE" = true ]; then
        build_args+=("--verbose")
    fi
    
    build_args+=("-j" "$JOBS")
    
    if ! cmake "${build_args[@]}"; then
        log_error "Build failed"
        exit 1
    fi
    
    log_success "Build completed successfully"
}

run_tests() {
    log_info "Running tests..."
    cd "$PROJECT_ROOT/build"
    
    if ! ctest --output-on-failure; then
        log_error "Tests failed"
        exit 1
    fi
    
    log_success "All tests passed"
}

# =============================================================================
# Main Script
# =============================================================================

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -t|--type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -f|--rebuild-finalcut)
            REBUILD_FINALCUT=true
            shift
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        --test)
            RUN_TESTS=true
            shift
            ;;
        -h|--help)
            print_usage
            exit 0
            ;;
        *)
            log_error "Unknown option: $1"
            print_usage
            exit 1
            ;;
    esac
done

# Validate build type
if [[ "$BUILD_TYPE" != "Debug" && "$BUILD_TYPE" != "Release" ]]; then
    log_error "Invalid build type: $BUILD_TYPE. Must be Debug or Release."
    exit 1
fi

# Print build configuration
echo "=========================================="
echo "Chinese Chess Build Configuration"
echo "=========================================="
echo "Build Type: $BUILD_TYPE"
echo "Clean Build: $CLEAN"
echo "Rebuild Finalcut: $REBUILD_FINALCUT"
echo "Run Tests: $RUN_TESTS"
echo "Parallel Jobs: $JOBS"
echo "Verbose: $VERBOSE"
echo "=========================================="

# Change to project root
cd "$PROJECT_ROOT"

# Check dependencies
check_dependencies

# Clean if requested
if [ "$CLEAN" = true ]; then
    clean_build
fi

# Rebuild finalcut if requested
if [ "$REBUILD_FINALCUT" = true ]; then
    rebuild_finalcut
fi

# Configure and build
configure_cmake
build_project

# Run tests if requested
if [ "$RUN_TESTS" = true ]; then
    run_tests
fi

# Final success message
echo ""
log_success "Build completed successfully!"
echo ""
echo "To run the game:"
echo "  ./run_game.sh"
echo ""
echo "To run tests:"
echo "  cd build && ctest"
echo ""
