#!/bin/bash

# =============================================================================
# Chinese Chess Test Runner Script
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
VERBOSE=false
FILTER=""
BUILD_DIR="$PROJECT_ROOT/build"

# =============================================================================
# Functions
# =============================================================================

print_usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -f, --filter PATTERN    Run only tests matching PATTERN"
    echo "  -v, --verbose           Verbose output"
    echo "  -b, --build-dir DIR     Build directory [default: build]"
    echo "  -h, --help              Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                      # Run all tests"
    echo "  $0 -f PointTest         # Run only PointTest tests"
    echo "  $0 -v                   # Run with verbose output"
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

check_build() {
    if [ ! -d "$BUILD_DIR" ]; then
        log_error "Build directory not found: $BUILD_DIR"
        log_info "Please build the project first with: ./scripts/build.sh"
        exit 1
    fi
    
    if [ ! -f "$BUILD_DIR/mainTest" ]; then
        log_error "Test executable not found: $BUILD_DIR/mainTest"
        log_info "Please build the project first with: ./scripts/build.sh"
        exit 1
    fi
}

run_ctest() {
    log_info "Running tests with CTest..."
    cd "$BUILD_DIR"
    
    local ctest_args=("--output-on-failure")
    
    if [ "$VERBOSE" = true ]; then
        ctest_args+=("--verbose")
    fi
    
    if [ -n "$FILTER" ]; then
        ctest_args+=("--filter" "$FILTER")
    fi
    
    if ! ctest "${ctest_args[@]}"; then
        log_error "Tests failed"
        return 1
    fi
    
    return 0
}

run_gtest() {
    log_info "Running tests with GoogleTest..."
    cd "$BUILD_DIR"
    
    local gtest_args=()
    
    if [ "$VERBOSE" = true ]; then
        gtest_args+=("--verbose")
    fi
    
    if [ -n "$FILTER" ]; then
        gtest_args+=("--gtest_filter=$FILTER")
    fi
    
    if ! ./mainTest "${gtest_args[@]}"; then
        log_error "Tests failed"
        return 1
    fi
    
    return 0
}

show_test_info() {
    log_info "Test Information:"
    echo "  Build Directory: $BUILD_DIR"
    echo "  Test Executable: $BUILD_DIR/mainTest"
    echo "  Filter: ${FILTER:-"All tests"}"
    echo "  Verbose: $VERBOSE"
    echo ""
}

# =============================================================================
# Main Script
# =============================================================================

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -f|--filter)
            FILTER="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -b|--build-dir)
            BUILD_DIR="$2"
            shift 2
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

# Change to project root
cd "$PROJECT_ROOT"

# Check if build exists
check_build

# Show test information
show_test_info

# Run tests
echo "=========================================="
echo "Running Chinese Chess Tests"
echo "=========================================="

if run_ctest; then
    echo ""
    log_success "All tests passed!"
    echo ""
    echo "Test Summary:"
    echo "  ✓ All tests completed successfully"
    echo "  ✓ No failures detected"
    echo ""
else
    echo ""
    log_error "Some tests failed!"
    echo ""
    echo "For more details, run:"
    echo "  $0 -v"
    echo ""
    exit 1
fi
