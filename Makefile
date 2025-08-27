# Compiler
CC = gcc
CXX = g++

# Build type (debug or release)
BUILD_TYPE ?= release

ONLY_BONGOCAT ?= 0

# Base flags
BASE_CFLAGS = -std=c23 -Iinclude -Isrc -isystem lib -isystem protocols # -fembed-dir=assets/
BASE_CFLAGS += -Wall -Wextra -Wpedantic -Wformat=2 -Wstrict-prototypes
BASE_CFLAGS += -Wmissing-prototypes -Wold-style-definition -Wredundant-decls
BASE_CFLAGS += -Wnested-externs -Wmissing-include-dirs -Wlogical-op
BASE_CFLAGS += -Wjump-misses-init -Wdouble-promotion -Wshadow
BASE_CFLAGS += -fstack-protector-strong

BASE_CXXFLAGS = -std=c++26 -Iinclude -Isrc -isystem lib -isystem protocols # -fembed-dir=assets/
BASE_CXXFLAGS += -Wall -Wextra -Wpedantic -Wformat=2
BASE_CXXFLAGS += -Wredundant-decls
BASE_CXXFLAGS += -Wmissing-include-dirs -Wlogical-op
BASE_CXXFLAGS += -Wdouble-promotion -Wshadow
BASE_CXXFLAGS += -fstack-protector-strong

ifeq ($(ONLY_BONGOCAT),1)
    BASE_CFLAGS += -DFEATURE_BONGOCAT_EMBEDDED_ASSETS
    BASE_CXXFLAGS += -DFEATURE_BONGOCAT_EMBEDDED_ASSETS
else
    BASE_CFLAGS += -DFEATURE_BONGOCAT_EMBEDDED_ASSETS -DFEATURE_ENABLE_DM_EMBEDDED_ASSETS -DFEATURE_MS_AGENT_EMBEDDED_ASSETS
    BASE_CXXFLAGS += -DFEATURE_BONGOCAT_EMBEDDED_ASSETS -DFEATURE_ENABLE_DM_EMBEDDED_ASSETS -DFEATURE_MS_AGENT_EMBEDDED_ASSETS
endif

# Debug flags
DEBUG_CFLAGS = $(BASE_CFLAGS) -g3 -O0 -DDEBUG -fsanitize=address -fsanitize=undefined
DEBUG_CXXFLAGS = $(BASE_CXXFLAGS) -g3 -O0 -DDEBUG -fsanitize=address -fsanitize=undefined
DEBUG_LDFLAGS = -fsanitize=address -fsanitize=undefined

# Release flags  
RELEASE_CFLAGS = $(BASE_CFLAGS) -O3 -DNDEBUG -flto -march=native -D_FORTIFY_SOURCE=2
RELEASE_CFLAGS += -fomit-frame-pointer -funroll-loops -finline-functions -D_FORTIFY_SOURCE=2
RELEASE_CXXFLAGS = $(BASE_CXXFLAGS) -O3 -DNDEBUG -flto -march=native -D_FORTIFY_SOURCE=2
RELEASE_CXXFLAGS += -fomit-frame-pointer -funroll-loops -finline-functions -D_FORTIFY_SOURCE=2

# Set flags based on build type
ifeq ($(BUILD_TYPE),debug)
    CFLAGS = $(DEBUG_CFLAGS)
    CXXFLAGS = $(DEBUG_CXXFLAGS)
    LDFLAGS = -lwayland-client -lm -lpthread -lrt $(DEBUG_LDFLAGS)
else
    CFLAGS = $(RELEASE_CFLAGS)
    CXXFLAGS = $(RELEASE_CXXFLAGS)
    LDFLAGS = -lwayland-client -lm -lpthread -lrt -flto
endif

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
PROTOCOLDIR = protocols
WAYLAND_PROTOCOLS_DIR ?= /usr/share/wayland-protocols

# Source files (including embedded assets which are now committed)
CXX_SRC = $(SRCDIR)/config/config.cpp \
    $(SRCDIR)/config/config_watcher.cpp \
    $(SRCDIR)/core/main.cpp \
    $(SRCDIR)/graphics/animation.cpp \
    $(SRCDIR)/graphics/animation_init.cpp \
    $(SRCDIR)/graphics/bar.cpp \
    $(SRCDIR)/graphics/drawing_images.cpp \
    $(SRCDIR)/graphics/load_images.cpp \
    $(SRCDIR)/graphics/embedded_assets.cpp \
    $(SRCDIR)/graphics/stb_image.cpp \
    $(SRCDIR)/platform/input.cpp \
    $(SRCDIR)/platform/wayland.cpp \
    $(SRCDIR)/utils/error.cpp \
    $(SRCDIR)/utils/memory.cpp \
    $(SRCDIR)/utils/system_memory.cpp \
    $(SRCDIR)/utils/time.cpp
CXX_SRC += $(SRCDIR)/graphics/embedded_assets_bongocat.cpp $(SRCDIR)/graphics/embedded_assets_dm.cpp $(SRCDIR)/graphics/embedded_assets_clippy.cpp
C_SRC = $(SRCDIR)/graphics/embedded_assets/bongocat_images.c $(SRCDIR)/graphics/embedded_assets/min_dm_images.c $(SRCDIR)/graphics/embedded_assets/clippy_images.c

C_OBJECTS = $(C_SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
CXX_OBJECTS = $(CXX_SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Protocol files
C_PROTOCOL_SRC = $(PROTOCOLDIR)/zwlr-layer-shell-v1-protocol.c $(PROTOCOLDIR)/xdg-shell-protocol.c $(PROTOCOLDIR)/wlr-foreign-toplevel-management-v1-protocol.c $(PROTOCOLDIR)/xdg-output-unstable-v1-protocol.c
H_PROTOCOL_HDR = $(PROTOCOLDIR)/zwlr-layer-shell-v1-client-protocol.h $(PROTOCOLDIR)/xdg-shell-client-protocol.h $(PROTOCOLDIR)/wlr-foreign-toplevel-management-v1-client-protocol.h $(PROTOCOLDIR)/xdg-output-unstable-v1-client-protocol.h
PROTOCOL_OBJECTS = $(C_PROTOCOL_SRC:$(PROTOCOLDIR)/%.c=$(OBJDIR)/%.o)

# Target executable
TARGET = $(BUILDDIR)/bongocat

.PHONY: all clean protocols

all: protocols $(TARGET)

# Generate protocol files first
protocols: $(C_PROTOCOL_SRC) $(H_PROTOCOL_HDR)

# Create build directories
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/core
	mkdir -p $(OBJDIR)/graphics
	mkdir -p $(OBJDIR)/graphics/embedded_assets
	mkdir -p $(OBJDIR)/platform
	mkdir -p $(OBJDIR)/config
	mkdir -p $(OBJDIR)/utils
	mkdir -p $(BUILDDIR)

# Compile source files (depends on protocol headers)
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(H_PROTOCOL_HDR) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile protocol files
$(OBJDIR)/%.o: $(PROTOCOLDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR)/%.o: $(PROTOCOLDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(TARGET): $(C_OBJECTS) $(CXX_OBJECTS) $(PROTOCOL_OBJECTS)
	$(CXX) $(C_OBJECTS) $(CXX_OBJECTS) $(PROTOCOL_OBJECTS) -o $(TARGET) $(LDFLAGS)

# Rule to generate Wayland protocol files
$(C_PROTOCOL_SRC) $(H_PROTOCOL_HDR): $(PROTOCOLDIR)/wlr-layer-shell-unstable-v1.xml $(PROTOCOLDIR)/wlr-foreign-toplevel-management-unstable-v1.xml $(PROTOCOLDIR)/xdg-output-unstable-v1.xml
	wayland-scanner client-header $(WAYLAND_PROTOCOLS_DIR)/stable/xdg-shell/xdg-shell.xml $(PROTOCOLDIR)/xdg-shell-client-protocol.h
	wayland-scanner private-code $(WAYLAND_PROTOCOLS_DIR)/stable/xdg-shell/xdg-shell.xml $(PROTOCOLDIR)/xdg-shell-protocol.c
	wayland-scanner private-code $(PROTOCOLDIR)/wlr-layer-shell-unstable-v1.xml $(PROTOCOLDIR)/zwlr-layer-shell-v1-protocol.c
	wayland-scanner client-header $(PROTOCOLDIR)/wlr-layer-shell-unstable-v1.xml $(PROTOCOLDIR)/zwlr-layer-shell-v1-client-protocol.h
	wayland-scanner private-code $(PROTOCOLDIR)/wlr-foreign-toplevel-management-unstable-v1.xml $(PROTOCOLDIR)/wlr-foreign-toplevel-management-v1-protocol.c
	wayland-scanner client-header $(PROTOCOLDIR)/wlr-foreign-toplevel-management-unstable-v1.xml $(PROTOCOLDIR)/wlr-foreign-toplevel-management-v1-client-protocol.h
	wayland-scanner client-header $(PROTOCOLDIR)/xdg-output-unstable-v1.xml $(PROTOCOLDIR)/xdg-output-unstable-v1-client-protocol.h
	wayland-scanner private-code $(PROTOCOLDIR)/xdg-output-unstable-v1.xml $(PROTOCOLDIR)/xdg-output-unstable-v1-protocol.c

clean:
	rm -rf $(BUILDDIR) $(C_PROTOCOL_SRC) $(H_PROTOCOL_HDR)

# Development targets
debug:
	$(MAKE) BUILD_TYPE=debug

release:
	$(MAKE) BUILD_TYPE=release

install: $(TARGET)
	install -D $(TARGET) $(DESTDIR)/usr/local/bin/bongocat
	install -D bongocat.conf $(DESTDIR)/usr/local/share/bongocat/bongocat.conf.example
	install -D scripts/find_input_devices.sh $(DESTDIR)/usr/local/bin/bongocat-find-devices

uninstall:
	rm -f $(DESTDIR)/usr/local/bin/bongocat
	rm -f $(DESTDIR)/usr/local/bin/bongocat-find-devices
	rm -rf $(DESTDIR)/usr/local/share/bongocat

# Static analysis
analyze:
	clang-tidy $(SOURCES) -- $(CFLAGS)

# Memory check (requires valgrind)
memcheck: debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Performance profiling
profile: release
	perf record -g ./$(TARGET)
	perf report

.PHONY: debug release install uninstall analyze memcheck profile
