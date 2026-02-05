#!/bin/bash

# =============================================================================
# Finalcut Library Build Script
# Cross-platform support for Linux and macOS
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
FINALCUT_VERSION="0.9.1"
CLEAN=true
VERBOSE=false

# Platform detection
if [[ "$OSTYPE" == "darwin"* ]]; then
    IS_MACOS=true
    JOBS=$(sysctl -n hw.ncpu)
    LIB_EXT="dylib"
else
    IS_MACOS=false
    JOBS=$(nproc)
    LIB_EXT="so"
fi

# =============================================================================
# Functions
# =============================================================================

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
    log_info "Checking build dependencies..."
    
    local missing_deps=()
    
    command -v git >/dev/null 2>&1 || missing_deps+=("git")
    command -v autoconf >/dev/null 2>&1 || missing_deps+=("autoconf")
    command -v automake >/dev/null 2>&1 || missing_deps+=("automake")
    command -v pkg-config >/dev/null 2>&1 || missing_deps+=("pkg-config")
    
    # Check for libtool (different names on different platforms)
    if [[ "$IS_MACOS" == true ]]; then
        # macOS with Homebrew uses glibtoolize
        if ! command -v glibtoolize >/dev/null 2>&1 && ! command -v libtoolize >/dev/null 2>&1; then
            missing_deps+=("libtool")
        fi
    else
        if ! command -v libtoolize >/dev/null 2>&1 && ! command -v libtool >/dev/null 2>&1; then
            missing_deps+=("libtool")
        fi
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        log_error "Missing dependencies: ${missing_deps[*]}"
        if [[ "$IS_MACOS" == true ]]; then
            log_info "Install them with: brew install ${missing_deps[*]}"
        else
            log_info "Install them with: sudo apt-get install ${missing_deps[*]}"
        fi
        exit 1
    fi
    
    log_success "All dependencies found"
}

clean_previous_build() {
    if [ "$CLEAN" = true ]; then
        log_info "Cleaning previous build..."
        rm -rf "$PROJECT_ROOT/finalcut"
        rm -rf "$PROJECT_ROOT/libfinal"
        rm -rf "$PROJECT_ROOT/final"
        log_success "Previous build cleaned"
    fi
}

download_finalcut() {
    log_info "Setting up finalcut library (version $FINALCUT_VERSION)..."
    
    cd "$PROJECT_ROOT"
    
    if [ ! -d "finalcut" ]; then
        # Use vendored copy from third_party/ (offline build)
        if [ -d "third_party/finalcut" ]; then
            log_info "Copying finalcut from vendored third_party/finalcut..."
            cp -r third_party/finalcut finalcut
            log_success "Finalcut copied from vendored source"
        else
            # Fallback: download from GitHub if vendored copy not available
            log_warning "Vendored finalcut not found, downloading from GitHub..."
            git clone --depth 1 --branch "$FINALCUT_VERSION" https://github.com/gansm/finalcut.git
            log_success "Finalcut downloaded from GitHub"
        fi
    else
        log_info "Finalcut directory already exists, skipping setup"
    fi
}

build_finalcut() {
    log_info "Building finalcut library..."
    
    cd "$PROJECT_ROOT/finalcut"
    
    # macOS: Set LIBTOOLIZE to glibtoolize if available
    if [[ "$IS_MACOS" == true ]]; then
        if command -v glibtoolize >/dev/null 2>&1; then
            export LIBTOOLIZE=glibtoolize
            log_info "Using glibtoolize for macOS"
        fi
    fi
    
    # Generate configure script
    log_info "Generating configure script..."
    autoreconf --install --force
    
    # Configure
    log_info "Configuring build..."
    
    # Create libfinal directory first so we can get absolute path
    mkdir -p "$PROJECT_ROOT/libfinal"
    
    local configure_args=(
        "--prefix=$PROJECT_ROOT/libfinal"
        "--enable-shared"
        "--disable-static"
    )
    
    if [ "$VERBOSE" = true ]; then
        configure_args+=("--verbose")
    fi
    
    if ! ./configure "${configure_args[@]}"; then
        log_error "Configure failed"
        exit 1
    fi
    
    # Build
    log_info "Building (using $JOBS parallel jobs)..."
    local make_args=("-j$JOBS")
    
    if [ "$VERBOSE" = true ]; then
        make_args+=("V=1")
    fi
    
    if ! make "${make_args[@]}"; then
        log_error "Build failed"
        exit 1
    fi
    
    log_success "Build completed"
}

install_finalcut() {
    log_info "Installing finalcut library..."
    
    cd "$PROJECT_ROOT/finalcut"
    
    # Install
    if ! make install; then
        log_error "Install failed"
        exit 1
    fi
    
    # Fix permissions
    chmod -R 755 "$PROJECT_ROOT/libfinal"
    
    # Move headers to expected location
    if [ -d "$PROJECT_ROOT/libfinal/include/final" ]; then
        mv "$PROJECT_ROOT/libfinal/include/final" "$PROJECT_ROOT/"
        log_info "Headers moved to project root"
    fi
    
    log_success "Installation completed"
}

verify_installation() {
    log_info "Verifying installation..."
    
    local lib_path="$PROJECT_ROOT/libfinal/lib/libfinal.${LIB_EXT}"
    local include_path="$PROJECT_ROOT/final"
    
    if [ ! -f "$lib_path" ]; then
        # Try alternative library patterns
        if [[ "$IS_MACOS" == true ]]; then
            lib_path=$(find "$PROJECT_ROOT/libfinal/lib" -name "libfinal*.dylib" 2>/dev/null | head -n1)
        else
            lib_path=$(find "$PROJECT_ROOT/libfinal/lib" -name "libfinal.so*" 2>/dev/null | head -n1)
        fi
        
        if [ -z "$lib_path" ] || [ ! -f "$lib_path" ]; then
            log_error "Library not found in: $PROJECT_ROOT/libfinal/lib/"
            ls -la "$PROJECT_ROOT/libfinal/lib/" 2>/dev/null || true
            return 1
        fi
    fi
    
    if [ ! -d "$include_path" ]; then
        log_error "Headers not found: $include_path"
        return 1
    fi
    
    log_success "Installation verified successfully"
    log_info "Library found at: $lib_path"
    return 0
}

cleanup() {
    log_info "Cleaning up build files..."
    cd "$PROJECT_ROOT"
    rm -rf finalcut
    log_success "Cleanup completed"
}

# =============================================================================
# Main Script
# =============================================================================

echo "=========================================="
echo "Finalcut Library Builder"
echo "=========================================="
echo "Version: $FINALCUT_VERSION"
echo "Platform: $(uname -s) ($(uname -m))"
echo "Library extension: $LIB_EXT"
echo "Clean Build: $CLEAN"
echo "Parallel Jobs: $JOBS"
echo "Verbose: $VERBOSE"
echo "=========================================="

# Change to project root
cd "$PROJECT_ROOT"

# Check dependencies
check_dependencies

# Clean previous build
clean_previous_build

# Download and build
download_finalcut
build_finalcut
install_finalcut

# Verify installation
if verify_installation; then
    log_success "Finalcut library built and installed successfully!"
    echo ""
    echo "Library: $PROJECT_ROOT/libfinal/lib/libfinal.${LIB_EXT}"
    echo "Headers: $PROJECT_ROOT/final/"
    echo ""
else
    log_error "Installation verification failed"
    exit 1
fi

# Cleanup
cleanup
