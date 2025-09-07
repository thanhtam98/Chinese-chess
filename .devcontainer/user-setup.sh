#!/bin/bash

# =============================================================================
# User Setup Script for Chinese Chess Dev Container
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
echo "User Setup for Chinese Chess"
echo "=========================================="

# Set up environment
log_info "Setting up environment..."
export LC_ALL=en_US.UTF-8
export LANG=en_US.UTF-8

# Add to bashrc
echo 'export LC_ALL=en_US.UTF-8' >> ~/.bashrc
echo 'export LANG=en_US.UTF-8' >> ~/.bashrc

# Set up git (if not already configured)
if [ ! -f ~/.gitconfig ]; then
    log_info "Setting up git configuration..."
    git config --global user.name "Chinese Chess Developer"
    git config --global user.email "developer@chinese-chess.local"
    git config --global init.defaultBranch main
fi

# Build the project
log_info "Building Chinese Chess project..."
cd /workspaces/Chinese-chess

# Make scripts executable
chmod +x scripts/*.sh
chmod +x run_game.sh

# Build the project
if make build; then
    log_success "Project built successfully!"
else
    log_warning "Build failed, but this is normal for first-time setup"
    log_info "You can run 'make setup' to complete the setup"
fi

# Run tests if build was successful
if [ -f "build/mainTest" ]; then
    log_info "Running tests..."
    if make test; then
        log_success "All tests passed!"
    else
        log_warning "Some tests failed"
    fi
fi

log_success "User setup completed!"
echo ""
echo "Development environment is ready!"
echo "Available commands:"
echo "  make help     - Show all available commands"
echo "  make build    - Build the project"
echo "  make run      - Run the game"
echo "  make test     - Run tests"
echo "  make clean    - Clean build directory"
echo ""
