BUILDDIR = build

ONLY_BONGOCAT ?= 1

ifeq ($(ONLY_BONGOCAT),1)
    FEATURES = -DFEATURE_BONGOCAT_EMBEDDED_ASSETS
else
    FEATURES = -DFEATURE_BONGOCAT_EMBEDDED_ASSETS -DFEATURE_ENABLE_DM_EMBEDDED_ASSETS -DFEATURE_MS_AGENT_EMBEDDED_ASSETS
endif


# Default target
default: build
all: build

.PHONY: all build release build-debug debug clean default install


# Release build
build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build
release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
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

# Clean build directory
clean:
	rm -rf build
