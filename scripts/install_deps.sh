#!/bin/bash

# =============================================================================
# Chinese Chess Dependency Installation Script
# =============================================================================

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

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

check_system() {
    log_info "Checking system information..."
    
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        if command -v apt-get >/dev/null 2>&1; then
            SYSTEM="ubuntu"
        elif command -v yum >/dev/null 2>&1; then
            SYSTEM="centos"
        elif command -v pacman >/dev/null 2>&1; then
            SYSTEM="arch"
        else
            log_error "Unsupported Linux distribution"
            exit 1
        fi
    else
        log_error "Unsupported operating system: $OSTYPE"
        exit 1
    fi
    
    log_success "Detected system: $SYSTEM"
}

install_ubuntu_deps() {
    log_info "Installing dependencies for Ubuntu/Debian..."
    
    # Update package list
    log_info "Updating package list..."
    $SUDO_CMD apt-get update -y
    
    # Install build tools
    log_info "Installing build tools..."
    $SUDO_CMD apt-get install -y \
        build-essential \
        cmake \
        git \
        pkg-config \
        autotools-dev \
        automake \
        autoconf \
        autoconf-archive \
        libtool
    
    # Install Boost
    log_info "Installing Boost libraries..."
    $SUDO_CMD apt-get install -y \
        libboost-all-dev
    
    # Install other dependencies
    log_info "Installing other dependencies..."
    $SUDO_CMD apt-get install -y \
        libncurses-dev \
        libtinfo-dev
    
    log_success "Ubuntu dependencies installed successfully"
}

install_centos_deps() {
    log_info "Installing dependencies for CentOS/RHEL..."
    
    # Install build tools
    log_info "Installing build tools..."
    $SUDO_CMD yum groupinstall -y "Development Tools"
    $SUDO_CMD yum install -y \
        cmake \
        git \
        pkgconfig \
        autotools \
        automake \
        autoconf \
        libtool
    
    # Install Boost
    log_info "Installing Boost libraries..."
    $SUDO_CMD yum install -y \
        boost-devel
    
    # Install other dependencies
    log_info "Installing other dependencies..."
    $SUDO_CMD yum install -y \
        ncurses-devel
    
    log_success "CentOS dependencies installed successfully"
}

install_arch_deps() {
    log_info "Installing dependencies for Arch Linux..."
    
    # Install build tools
    log_info "Installing build tools..."
    $SUDO_CMD pacman -S --noconfirm \
        base-devel \
        cmake \
        git \
        pkg-config \
        autotools \
        automake \
        autoconf \
        libtool
    
    # Install Boost
    log_info "Installing Boost libraries..."
    $SUDO_CMD pacman -S --noconfirm \
        boost
    
    # Install other dependencies
    log_info "Installing other dependencies..."
    $SUDO_CMD pacman -S --noconfirm \
        ncurses
    
    log_success "Arch dependencies installed successfully"
}

verify_installation() {
    log_info "Verifying installation..."
    
    local missing_tools=()
    
    # Check for required tools
    command -v cmake >/dev/null 2>&1 || missing_tools+=("cmake")
    command -v g++ >/dev/null 2>&1 || missing_tools+=("g++")
    command -v git >/dev/null 2>&1 || missing_tools+=("git")
    command -v pkg-config >/dev/null 2>&1 || missing_tools+=("pkg-config")
    
    # Check for Boost (try multiple ways)
    if ! pkg-config --exists libboost-system && ! ldconfig -p | grep -q libboost_system; then
        missing_tools+=("boost")
    fi
    
    if [ ${#missing_tools[@]} -ne 0 ]; then
        log_error "Missing tools after installation: ${missing_tools[*]}"
        return 1
    fi
    
    log_success "All dependencies verified successfully"
    return 0
}

# =============================================================================
# Main Script
# =============================================================================

echo "=========================================="
echo "Chinese Chess Dependency Installer"
echo "=========================================="

# Check if running as root
if [[ $EUID -eq 0 ]]; then
    log_warning "Running as root - this is OK in containerized environments"
    log_info "Proceeding with installation..."
    # In containerized environments, we can run as root
    # Remove sudo from commands when running as root
    SUDO_CMD=""
else
    log_info "Running as regular user - using sudo for package installation"
    SUDO_CMD="sudo"
fi

# Check system and install dependencies
check_system

case $SYSTEM in
    ubuntu)
        install_ubuntu_deps
        ;;
    centos)
        install_centos_deps
        ;;
    arch)
        install_arch_deps
        ;;
    *)
        log_error "Unsupported system: $SYSTEM"
        exit 1
        ;;
esac

# Verify installation
if verify_installation; then
    echo ""
    log_success "All dependencies installed successfully!"
    echo ""
    echo "You can now build the project with:"
    echo "  ./scripts/build.sh"
    echo ""
else
    log_error "Dependency verification failed"
    exit 1
fi
