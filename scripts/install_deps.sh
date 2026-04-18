#!/bin/bash

# =============================================================================
# Chinese Chess Dependency Installation Script
# Cross-platform support for Linux and macOS
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
    
    if [[ "$OSTYPE" == "darwin"* ]]; then
        SYSTEM="macos"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
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

install_macos_deps() {
    log_info "Installing dependencies for macOS..."
    
    # Check for Homebrew
    if ! command -v brew >/dev/null 2>&1; then
        log_error "Homebrew not found."
        log_info "Install Homebrew first: /bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
        exit 1
    fi
    
    log_info "Updating Homebrew..."
    brew update
    
    # Install build tools
    log_info "Installing build tools..."
    brew install cmake git pkg-config autoconf automake libtool autoconf-archive
    
    # Install Boost (includes Beast for WebSocket)
    log_info "Installing Boost libraries..."
    brew install boost
    
    # Install ncurses (for Finalcut)
    log_info "Installing ncurses..."
    brew install ncurses
    
    # Install tmux (for running server/client in split panes)
    log_info "Installing tmux..."
    brew install tmux
    
    log_success "macOS dependencies installed successfully"
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
        libtinfo-dev \
        tmux
    
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
        ncurses-devel \
        tmux
    
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
        ncurses \
        tmux
    
    log_success "Arch dependencies installed successfully"
}

verify_installation() {
    log_info "Verifying installation..."
    
    local missing_tools=()
    
    # Check for required tools
    command -v cmake >/dev/null 2>&1 || missing_tools+=("cmake")
    command -v git >/dev/null 2>&1 || missing_tools+=("git")
    command -v pkg-config >/dev/null 2>&1 || missing_tools+=("pkg-config")
    
    # Check for C++ compiler
    if [[ "$SYSTEM" == "macos" ]]; then
        command -v clang++ >/dev/null 2>&1 || missing_tools+=("clang++")
    else
        command -v g++ >/dev/null 2>&1 || missing_tools+=("g++")
    fi
    
    # Check for Boost
    if [[ "$SYSTEM" == "macos" ]]; then
        # On macOS, check if Boost is installed via Homebrew
        if ! brew list boost &>/dev/null; then
            missing_tools+=("boost")
        fi
    else
        # On Linux, check via pkg-config or ldconfig
        if ! pkg-config --exists libboost-system 2>/dev/null && ! ldconfig -p 2>/dev/null | grep -q libboost_system; then
            # Try alternative check
            if [ ! -d "/usr/include/boost" ] && [ ! -d "/usr/local/include/boost" ]; then
                missing_tools+=("boost")
            fi
        fi
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
echo "Platform: $(uname -s) ($(uname -m))"
echo "=========================================="

# Check if running as root (not applicable on macOS)
if [[ "$OSTYPE" == "darwin"* ]]; then
    SUDO_CMD=""
elif [[ $EUID -eq 0 ]]; then
    log_warning "Running as root - this is OK in containerized environments"
    log_info "Proceeding with installation..."
    SUDO_CMD=""
else
    log_info "Running as regular user - using sudo for package installation"
    SUDO_CMD="sudo"
fi

# Check system and install dependencies
check_system

case $SYSTEM in
    macos)
        install_macos_deps
        ;;
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
    echo "  make setup    # Full setup (deps + finalcut + build)"
    echo "  make build    # Build only"
    echo ""
else
    log_error "Dependency verification failed"
    exit 1
fi
