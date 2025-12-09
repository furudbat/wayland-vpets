# keep Makefile for older scripts, cmake still needed

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
PROTOCOLDIR = protocols
WAYLAND_PROTOCOLS_DIR ?= /usr/share/wayland-protocols

ONLY_BONGOCAT ?= 1

ifeq ($(ONLY_BONGOCAT),1)
    FEATURES = -DFEATURE_BONGOCAT_EMBEDDED_ASSETS
else
    FEATURES = -DFEATURE_BONGOCAT_EMBEDDED_ASSETS -DFEATURE_ENABLE_DM_EMBEDDED_ASSETS -DFEATURE_MS_AGENT_EMBEDDED_ASSETS -DFEATURE_PKMN_EMBEDDED_ASSETS
endif

# Target executable
TARGET = $(BUILDDIR)/bongocat

.PHONY: all format format-check lint

# Default target
default: build
all: build

# Release build
build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build
release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DFEATURE_LAZY_LOAD_ASSETS=ON -DFEATURE_MULTI_VERSIONS=ON
	cmake --build build

# Debug build
build-debug:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build
debug:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build

# Install target
install: build
	cmake --install build

pack: release doc
	cd build && cpack

doc: release
	cmake --build build --target manpages

SOURCES = $(shell find $(SRCDIR) -name '*.cpp' ! -path '*/embedded_assets/**/*.c??' ! -path '*/image_loader/*.c' ! -path '*/image_loader/**/*.cpp')
# Static analysis
analyze:
	clang-tidy -p build $(SOURCES)

# Memory check (requires valgrind)
memcheck: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Performance profiling
profile: release
	perf record -g ./$(TARGET)
	perf report

# =============================================================================
# CODE QUALITY TARGETS
# =============================================================================

# Find all project source files (exclude lib/ and protocols/)
PROJECT_SOURCES = $(shell find $(SRCDIR) -name '*.cpp' ! -path '*/embedded_assets/**/*.c??' ! -path '*/image_loader/*.c' ! -path '*/image_loader/**/*.cpp')
PROJECT_HEADERS = $(shell find $(INCDIR) -name '*.h' ! -path '*/embedded_assets/**/*.h' ! -path '*/image_loader/**/*.h')
ALL_PROJECT_FILES = $(PROJECT_SOURCES) $(PROJECT_HEADERS)

# Format all project source files
format:
	cmake --build build --target fix-format

# Check if formatting is correct (for CI)
format-check:
	cmake --build build --target check-format

# Static analysis with clang-tidy (uses .clang-tidy config)
lint: protocols
	@echo "Running static analysis..."
	@clang-tidy -p build $(PROJECT_SOURCES) 2>/dev/null || true
	@echo "Static analysis complete."

# Alias for lint
analyze: lint

# Generate compile_commands.json for IDE support, or just use cmake and presets
# Run: make compiledb
compiledb: clean
	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

.PHONY: compiledb