# Taquin - Sliding Puzzle Game Makefile
# Cross-platform build system for Windows, Linux, and macOS

# Project configuration
PROJECT_NAME = taquin
VERSION = 2.0

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -DNDEBUG

# Source files
SOURCES = main.c game.c render.c
HEADERS = constant.h functions.h
OBJECTS = $(SOURCES:.c=.o)

# Directories
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin
OBJ_DIR = obj

# Platform detection
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
    # Linux settings
    PLATFORM = linux
    SDL2_CFLAGS = $(shell pkg-config --cflags sdl2)
    SDL2_LIBS = $(shell pkg-config --libs sdl2)
    EXECUTABLE = $(PROJECT_NAME)
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME_S),Darwin)
    # macOS settings
    PLATFORM = macos
    SDL2_CFLAGS = $(shell pkg-config --cflags sdl2)
    SDL2_LIBS = $(shell pkg-config --libs sdl2)
    EXECUTABLE = $(PROJECT_NAME)
    INSTALL_DIR = /usr/local/bin
endif

ifeq ($(UNAME_S),Windows)
    # Windows settings (MinGW)
    PLATFORM = windows
    SDL2_CFLAGS = -IC:/development/i686-w64-mingw32/include/SDL2 -IC:/development/SDL2/x86_64-w64-mingw32/include/SDL2
    SDL2_LIBS = -LC:/development/i686-w64-mingw32/lib -LC:/development/SDL2/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2
    EXECUTABLE = $(PROJECT_NAME).exe
    INSTALL_DIR = C:/Program Files/$(PROJECT_NAME)
endif

# If no platform detected, assume Windows
ifndef PLATFORM
    PLATFORM = windows
    SDL2_CFLAGS = -IC:/development/i686-w64-mingw32/include/SDL2 -IC:/development/SDL2/x86_64-w64-mingw32/include/SDL2
    SDL2_LIBS = -LC:/development/i686-w64-mingw32/lib -LC:/development/SDL2/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2
    EXECUTABLE = $(PROJECT_NAME).exe
    INSTALL_DIR = C:/Program Files/$(PROJECT_NAME)
endif

# Complete compiler flags
ALL_CFLAGS = $(CFLAGS) $(SDL2_CFLAGS)
ALL_LIBS = $(SDL2_LIBS)

# Default target
all: release

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Object file compilation
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(ALL_CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(BIN_DIR)/$(EXECUTABLE)

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: $(BIN_DIR)/$(EXECUTABLE)

# Link executable
$(BIN_DIR)/$(EXECUTABLE): $(addprefix $(OBJ_DIR)/,$(OBJECTS)) | $(BIN_DIR)
	$(CC) $^ -o $@ $(ALL_LIBS)
	@echo "Build complete: $@"

# Clean build files
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	@echo "Clean complete"

# Install (Unix-like systems)
install: release
ifeq ($(PLATFORM),windows)
	@echo "Install not supported on Windows. Copy $(BIN_DIR)/$(EXECUTABLE) manually."
else
	sudo cp $(BIN_DIR)/$(EXECUTABLE) $(INSTALL_DIR)/
	sudo chmod +x $(INSTALL_DIR)/$(EXECUTABLE)
	@echo "Installed to $(INSTALL_DIR)/$(EXECUTABLE)"
endif

# Uninstall (Unix-like systems)
uninstall:
ifeq ($(PLATFORM),windows)
	@echo "Uninstall not supported on Windows. Remove files manually."
else
	sudo rm -f $(INSTALL_DIR)/$(EXECUTABLE)
	@echo "Uninstalled $(EXECUTABLE)"
endif

# Run the game
run: release
	./$(BIN_DIR)/$(EXECUTABLE)

# Package for distribution
package: release
	mkdir -p $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
	cp $(BIN_DIR)/$(EXECUTABLE) $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/
	cp -r images $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/
	cp README.md $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/
	cp LICENSE $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/ 2>/dev/null || true
ifeq ($(PLATFORM),windows)
	cp SDL2.dll $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/ 2>/dev/null || true
	zip -r $(PROJECT_NAME)-$(VERSION)-$(PLATFORM).zip $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
else
	tar -czf $(PROJECT_NAME)-$(VERSION)-$(PLATFORM).tar.gz $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
endif
	rm -rf $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
	@echo "Package created: $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)"

# Help
help:
	@echo "Taquin - Sliding Puzzle Game Build System"
	@echo "Platform: $(PLATFORM)"
	@echo ""
	@echo "Available targets:"
	@echo "  all       - Build release version (default)"
	@echo "  debug     - Build debug version"
	@echo "  release   - Build release version"
	@echo "  clean     - Remove build files"
	@echo "  run       - Build and run the game"
	@echo "  install   - Install to system (Unix-like only)"
	@echo "  uninstall - Remove from system (Unix-like only)"
	@echo "  package   - Create distribution package"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make debug    - Build debug version"
	@echo "  make clean    - Clean build files"
	@echo "  make run      - Build and run"

# Phony targets
.PHONY: all debug release clean install uninstall run package help

# Dependencies
main.o: main.c functions.h constant.h
game.o: game.c functions.h constant.h
render.o: render.c functions.h constant.h
