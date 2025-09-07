#!/bin/bash

# =============================================================================
# Dev Container Setup Script for Chinese Chess
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

# =============================================================================
# Main Setup
# =============================================================================

echo "=========================================="
echo "Chinese Chess Dev Container Setup"
echo "=========================================="

# Update package list
log_info "Updating package list..."
apt-get update -y

# Install essential build tools
log_info "Installing build tools..."
apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    autotools-dev \
    automake \
    autoconf \
    autoconf-archive \
    libtool \
    curl \
    wget \
    unzip \
    vim \
    nano

# Install Boost libraries
log_info "Installing Boost libraries..."
apt-get install -y \
    libboost-all-dev

# Install other dependencies
log_info "Installing other dependencies..."
apt-get install -y \
    libncurses-dev \
    libtinfo-dev \
    gdb \
    valgrind

# Install additional development tools
log_info "Installing development tools..."
apt-get install -y \
    clang-format \
    clang-tidy \
    cppcheck \
    gcovr \
    lcov

# Set up locale
log_info "Setting up locale..."
apt-get install -y locales
locale-gen en_US.UTF-8
update-locale LANG=en_US.UTF-8

# Create vscode user if it doesn't exist
if ! id "vscode" &>/dev/null; then
    log_info "Creating vscode user..."
    useradd -m -s /bin/bash vscode
    usermod -aG sudo vscode
    echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
fi

# Set up workspace permissions
log_info "Setting up workspace permissions..."
chown -R vscode:vscode /workspaces/Chinese-chess
chmod -R 755 /workspaces/Chinese-chess

# Switch to vscode user for remaining setup
log_info "Switching to vscode user for project setup..."
su - vscode -c "cd /workspaces/Chinese-chess && bash -c 'source .devcontainer/user-setup.sh'"

log_success "Dev container setup completed!"
echo ""
echo "You can now:"
echo "  1. Build the project: make build"
echo "  2. Run the game: make run"
echo "  3. Run tests: make test"
echo "  4. Get help: make help"
echo ""
