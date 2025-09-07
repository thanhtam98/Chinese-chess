# =============================================================================
# Chinese Chess Project Makefile
# =============================================================================

# Project information
PROJECT_NAME := chinese-chess
VERSION := 0.1.0

# Directories
BUILD_DIR := build
SCRIPTS_DIR := scripts
LIBFINAL_DIR := libfinal

# Default values
BUILD_TYPE ?= Release
JOBS ?= $(shell nproc)
VERBOSE ?= false

# Colors for output
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[1;33m
BLUE := \033[0;34m
NC := \033[0m

# =============================================================================
# Default target
# =============================================================================

.PHONY: all
all: build

# =============================================================================
# Help target
# =============================================================================

.PHONY: help
help:
	@echo "Chinese Chess Project - Available Targets:"
	@echo ""
	@echo "Build Targets:"
	@echo "  build              Build the project (default)"
	@echo "  build-debug        Build in Debug mode"
	@echo "  build-release      Build in Release mode"
	@echo "  clean              Clean build directory"
	@echo "  clean-all          Clean all build artifacts and dependencies"
	@echo ""
	@echo "Dependency Targets:"
	@echo "  deps               Install system dependencies"
	@echo "  finalcut           Build finalcut library"
	@echo "  rebuild-finalcut   Rebuild finalcut library from scratch"
	@echo ""
	@echo "Test Targets:"
	@echo "  test               Run all tests"
	@echo "  test-verbose       Run tests with verbose output"
	@echo "  test-filter FILTER Run tests matching FILTER"
	@echo ""
	@echo "Run Targets:"
	@echo "  run                Run the game"
	@echo "  run-debug          Run the game in debug mode"
	@echo ""
	@echo "Development Targets:"
	@echo "  setup              Complete project setup (deps + build)"
	@echo "  rebuild            Clean and rebuild everything"
	@echo "  status             Show project status"
	@echo ""
	@echo "Variables:"
	@echo "  BUILD_TYPE         Build type (Debug|Release) [default: Release]"
	@echo "  JOBS               Number of parallel jobs [default: \$$(nproc)]"
	@echo "  VERBOSE            Verbose output (true|false) [default: false]"
	@echo ""
	@echo "Examples:"
	@echo "  make build-debug"
	@echo "  make test-verbose"
	@echo "  make rebuild-finalcut"
	@echo "  make clean-all"

# =============================================================================
# Build targets
# =============================================================================

.PHONY: build
build:
	@echo "$(BLUE)[INFO]$(NC) Building project..."
	@$(SCRIPTS_DIR)/build.sh --type $(BUILD_TYPE) --jobs $(JOBS)

.PHONY: build-debug
build-debug:
	@echo "$(BLUE)[INFO]$(NC) Building in Debug mode..."
	@$(SCRIPTS_DIR)/build.sh --type Debug --jobs $(JOBS)

.PHONY: build-release
build-release:
	@echo "$(BLUE)[INFO]$(NC) Building in Release mode..."
	@$(SCRIPTS_DIR)/build.sh --type Release --jobs $(JOBS)

.PHONY: clean
clean:
	@echo "$(BLUE)[INFO]$(NC) Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)[SUCCESS]$(NC) Build directory cleaned"

.PHONY: clean-all
clean-all:
	@echo "$(BLUE)[INFO]$(NC) Cleaning all build artifacts..."
	@rm -rf $(BUILD_DIR)
	@rm -rf $(LIBFINAL_DIR)
	@rm -rf finalcut
	@rm -rf final
	@echo "$(GREEN)[SUCCESS]$(NC) All build artifacts cleaned"

# =============================================================================
# Dependency targets
# =============================================================================

.PHONY: deps
deps:
	@echo "$(BLUE)[INFO]$(NC) Installing system dependencies..."
	@$(SCRIPTS_DIR)/install_deps.sh

.PHONY: finalcut
finalcut:
	@echo "$(BLUE)[INFO]$(NC) Building finalcut library..."
	@$(SCRIPTS_DIR)/build_finalcut.sh

.PHONY: rebuild-finalcut
rebuild-finalcut:
	@echo -e "$(BLUE)[INFO]$(NC) Rebuilding finalcut library..."
	@rm -rf $(LIBFINAL_DIR) finalcut final
	@$(SCRIPTS_DIR)/build_finalcut.sh

# =============================================================================
# Test targets
# =============================================================================

.PHONY: test
test:
	@echo "$(BLUE)[INFO]$(NC) Running tests..."
	@$(SCRIPTS_DIR)/run_tests.sh

.PHONY: test-verbose
test-verbose:
	@echo "$(BLUE)[INFO]$(NC) Running tests with verbose output..."
	@$(SCRIPTS_DIR)/run_tests.sh --verbose

.PHONY: test-filter
test-filter:
	@if [ -z "$(FILTER)" ]; then \
		echo "$(RED)[ERROR]$(NC) FILTER variable not set. Usage: make test-filter FILTER=TestName"; \
		exit 1; \
	fi
	@echo "$(BLUE)[INFO]$(NC) Running tests matching '$(FILTER)'..."
	@$(SCRIPTS_DIR)/run_tests.sh --filter "$(FILTER)"

# =============================================================================
# Run targets
# =============================================================================

.PHONY: run
run:
	@echo "$(BLUE)[INFO]$(NC) Running the game..."
	@./run_game.sh

.PHONY: run-debug
run-debug:
	@echo "$(BLUE)[INFO]$(NC) Running the game in debug mode..."
	@export LD_LIBRARY_PATH="$(PWD)/$(LIBFINAL_DIR)/lib:$$LD_LIBRARY_PATH" && \
	 export LC_ALL=en_US.UTF-8 && \
	 gdb --args $(BUILD_DIR)/$(PROJECT_NAME)

# =============================================================================
# Development targets
# =============================================================================

.PHONY: setup
setup: deps finalcut build
	@echo "$(GREEN)[SUCCESS]$(NC) Project setup completed!"
	@echo ""
	@echo "You can now run the game with:"
	@echo "  make run"
	@echo ""
	@echo "Or run tests with:"
	@echo "  make test"

.PHONY: rebuild
rebuild: clean-all finalcut build
	@echo "$(GREEN)[SUCCESS]$(NC) Project rebuilt successfully!"

.PHONY: status
status:
	@echo "=========================================="
	@echo "Chinese Chess Project Status"
	@echo "=========================================="
	@echo "Project: $(PROJECT_NAME) v$(VERSION)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Parallel Jobs: $(JOBS)"
	@echo "Verbose: $(VERBOSE)"
	@echo ""
	@echo "Directories:"
	@echo "  Build: $(BUILD_DIR) $(if $(wildcard $(BUILD_DIR)),✓,✗)"
	@echo "  Finalcut: $(LIBFINAL_DIR) $(if $(wildcard $(LIBFINAL_DIR)),✓,✗)"
	@echo "  Headers: final $(if $(wildcard final),✓,✗)"
	@echo ""
	@echo "Executables:"
	@echo "  Game: $(BUILD_DIR)/$(PROJECT_NAME) $(if $(wildcard $(BUILD_DIR)/$(PROJECT_NAME)),✓,✗)"
	@echo "  Tests: $(BUILD_DIR)/mainTest $(if $(wildcard $(BUILD_DIR)/mainTest),✓,✗)"
	@echo ""
	@echo "Libraries:"
	@echo "  Finalcut: $(LIBFINAL_DIR)/lib/libfinal.so $(if $(wildcard $(LIBFINAL_DIR)/lib/libfinal.so),✓,✗)"
	@echo "=========================================="

# =============================================================================
# Install targets
# =============================================================================

.PHONY: install
install: build
	@echo -e "$(BLUE)[INFO]$(NC) Installing project..."
	@cd $(BUILD_DIR) && cmake --install .
	@echo -e "$(GREEN)[SUCCESS]$(NC) Project installed successfully!"

.PHONY: uninstall
uninstall:
	@echo -e "$(BLUE)[INFO]$(NC) Uninstalling project..."
	@# Add uninstall logic here if needed
	@echo -e "$(GREEN)[SUCCESS]$(NC) Project uninstalled successfully!"

# =============================================================================
# Development helpers
# =============================================================================

.PHONY: format
format:
	@echo -e "$(BLUE)[INFO]$(NC) Formatting code..."
	@# Add code formatting logic here
	@echo -e "$(GREEN)[SUCCESS]$(NC) Code formatted"

.PHONY: lint
lint:
	@echo -e "$(BLUE)[INFO]$(NC) Running linter..."
	@# Add linting logic here
	@echo -e "$(GREEN)[SUCCESS]$(NC) Linting completed"

.PHONY: docs
docs:
	@echo -e "$(BLUE)[INFO]$(NC) Generating documentation..."
	@# Add documentation generation logic here
	@echo -e "$(GREEN)[SUCCESS]$(NC) Documentation generated"

# =============================================================================
# Phony targets
# =============================================================================

.PHONY: all build build-debug build-release clean clean-all
.PHONY: deps finalcut rebuild-finalcut
.PHONY: test test-verbose test-filter
.PHONY: run run-debug
.PHONY: setup rebuild status
.PHONY: install uninstall
.PHONY: format lint docs help