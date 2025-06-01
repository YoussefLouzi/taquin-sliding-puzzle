# 🧩 Taquin - Enhanced Sliding Puzzle Game

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-blue.svg)](https://github.com/yourusername/taquin)
[![Language](https://img.shields.io/badge/Language-C-green.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![SDL2](https://img.shields.io/badge/Graphics-SDL2-red.svg)](https://www.libsdl.org/)

A modern, feature-rich implementation of the classic sliding puzzle game (also known as the 15-puzzle or n-puzzle) built with SDL2. This enhanced version includes multiple difficulty levels, smooth animations, scoring system, and professional code organization.

![Game Screenshot](docs/screenshot.png)

## ✨ Features

### 🎮 Gameplay
- **Multiple Difficulty Levels**: 3×3, 4×4, and 5×5 grid sizes
- **Smooth Animations**: Fluid tile sliding animations
- **Intuitive Controls**: Mouse click to move tiles
- **Smart Shuffling**: Ensures solvable puzzle configurations
- **Win Detection**: Automatic victory condition checking

### 📊 Statistics & Scoring
- **Move Counter**: Track your efficiency
- **Timer**: See how fast you can solve puzzles
- **Best Scores**: Personal records for each difficulty level
- **Performance Tracking**: Compare your improvements over time

### 🎨 Visual Design
- **Modern UI**: Clean, professional interface
- **Responsive Layout**: Adapts to different grid sizes
- **Visual Feedback**: Clear tile borders and hover effects
- **Custom Graphics**: Professional number tile designs

### 🔧 Technical Features
- **Cross-Platform**: Windows, Linux, and macOS support
- **Memory Safe**: Proper resource management and cleanup
- **Modular Code**: Well-organized, maintainable codebase
- **Error Handling**: Robust error checking and recovery

## 🚀 Quick Start

### Prerequisites

- **C Compiler**: GCC, Clang, or MSVC
- **SDL2 Development Libraries**: Version 2.0 or higher
- **Make**: For building (optional, but recommended)

### Installation

#### Windows (MinGW/MSYS2)
```bash
# Install SDL2 development libraries
pacman -S mingw-w64-x86_64-SDL2

# Clone and build
git clone https://github.com/yourusername/taquin.git
cd taquin
make release
```

#### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt-get install libsdl2-dev build-essential

# Clone and build
git clone https://github.com/yourusername/taquin.git
cd taquin
make release
```

#### macOS
```bash
# Install dependencies (using Homebrew)
brew install sdl2

# Clone and build
git clone https://github.com/yourusername/taquin.git
cd taquin
make release
```

### Running the Game

```bash
# Run directly
make run

# Or run the executable
./bin/taquin        # Linux/macOS
./bin/taquin.exe    # Windows
```

## 🎯 How to Play

### Objective
Arrange the numbered tiles in order from 1 to n² (where n is the grid size), with the empty space in the bottom-right corner.

### Controls

#### Menu Navigation
- **3, 4, 5**: Select grid size (3×3, 4×4, 5×5)
- **Q/ESC**: Quit game

#### In-Game Controls
- **Mouse Click**: Move tile adjacent to empty space
- **ESC**: Return to main menu
- **R**: Reset current puzzle
- **N**: Generate new shuffle
- **Q**: Quit to desktop

#### Win Screen
- **SPACE/ENTER**: Return to menu
- **R**: Play again with same difficulty

### Strategy Tips
1. **Start with corners**: Position corner pieces first
2. **Work row by row**: Complete the top rows before moving to bottom
3. **Use the empty space**: Plan moves to create working space
4. **Think ahead**: Consider the consequences of each move

## 🏗️ Building from Source

### Build Options

```bash
# Release build (optimized)
make release

# Debug build (with debugging symbols)
make debug

# Clean build files
make clean

# Create distribution package
make package

# Install system-wide (Linux/macOS)
sudo make install
```

### Build Configuration

The Makefile automatically detects your platform and configures appropriate settings:

- **Windows**: Uses MinGW with bundled SDL2
- **Linux**: Uses pkg-config to find SDL2
- **macOS**: Uses Homebrew SDL2 installation

### Custom SDL2 Path

If SDL2 is installed in a custom location, set the paths manually:

```bash
# Example for custom Windows installation
make SDL2_CFLAGS="-IC:/custom/SDL2/include" SDL2_LIBS="-LC:/custom/SDL2/lib -lSDL2main -lSDL2"
```

## 📁 Project Structure

```
taquin/
├── src/
│   ├── main.c          # Main game loop and initialization
│   ├── game.c          # Core game logic and state management
│   ├── render.c        # Rendering and graphics functions
│   ├── constant.h      # Game constants and data structures
│   └── functions.h     # Function declarations
├── images/
│   ├── interface/      # Menu and UI graphics
│   └── numbers/        # Number tile graphics
├── bin/                # Compiled executables
├── obj/                # Object files
├── docs/               # Documentation and screenshots
├── Makefile           # Build configuration
├── README.md          # This file
└── LICENSE            # License information
```

## 🔧 Development

### Code Organization

The codebase is organized into logical modules:

- **main.c**: Entry point, main game loop, and event handling
- **game.c**: Game logic, board management, and state transitions
- **render.c**: Graphics rendering, animations, and visual effects
- **constant.h**: Constants, data structures, and type definitions
- **functions.h**: Function declarations and API documentation

### Adding Features

The modular design makes it easy to extend the game:

1. **New Game Modes**: Add to `GameState` enum and implement handlers
2. **Visual Effects**: Extend rendering functions in `render.c`
3. **Input Methods**: Add handlers in the input processing section
4. **Scoring Systems**: Extend the `GameStats` structure

### Debugging

Build with debug symbols and run with a debugger:

```bash
make debug
gdb ./bin/taquin        # Linux
lldb ./bin/taquin       # macOS
```

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development Guidelines

1. **Code Style**: Follow the existing code style and formatting
2. **Documentation**: Update documentation for new features
3. **Testing**: Test on multiple platforms when possible
4. **Commits**: Use clear, descriptive commit messages

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **SDL2 Team**: For the excellent graphics library
- **Original Taquin**: Inspired by the classic sliding puzzle game
- **Contributors**: Thanks to all who have contributed to this project

## 📞 Support

If you encounter any issues or have questions:

1. Check the [Issues](https://github.com/yourusername/taquin/issues) page
2. Create a new issue with detailed information
3. Include your platform, SDL2 version, and error messages

---

**Enjoy playing Taquin! 🎮**
