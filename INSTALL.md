# Installation Guide - Taquin Sliding Puzzle Game

This guide will help you set up the development environment and build the Taquin game on different platforms.

## 📋 Prerequisites

### All Platforms
- **C Compiler**: GCC, Clang, or MSVC
- **SDL2 Development Libraries**: Version 2.0 or higher
- **Make** (optional but recommended)

## 🪟 Windows Installation

### Option 1: Using MinGW/MSYS2 (Recommended)

1. **Install MSYS2**
   - Download from: https://www.msys2.org/
   - Follow the installation instructions
   - Update the package database:
     ```bash
     pacman -Syu
     ```

2. **Install Development Tools**
   ```bash
   # Install GCC and Make
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make
   
   # Install SDL2
   pacman -S mingw-w64-x86_64-SDL2
   ```

3. **Build the Game**
   ```bash
   # Clone or download the project
   cd taquin
   make release
   ```

### Option 2: Manual SDL2 Setup

1. **Download SDL2**
   - Go to: https://www.libsdl.org/download-2.0.php
   - Download "Development Libraries" for MinGW

2. **Extract SDL2**
   - Extract to `C:/development/SDL2/`
   - The structure should be:
     ```
     C:/development/SDL2/
     ├── include/SDL2/
     ├── lib/
     └── bin/
     ```

3. **Install MinGW**
   - Download from: http://mingw-w64.org/
   - Or use TDM-GCC: https://jmeubank.github.io/tdm-gcc/

4. **Build the Game**
   ```bash
   # Use the provided batch file
   build.bat
   
   # Or use make if available
   make release
   ```

### Option 3: Using Code::Blocks (Original Setup)

If you prefer to use the original Code::Blocks setup:

1. **Install Code::Blocks**
   - Download from: http://www.codeblocks.org/

2. **Set up SDL2**
   - Follow the paths in `projet_c.cbp`
   - Ensure SDL2 is installed in the expected directories

3. **Open and Build**
   - Open `projet_c.cbp` in Code::Blocks
   - Build and run the project

## 🐧 Linux Installation

### Ubuntu/Debian
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential libsdl2-dev

# Clone and build
git clone <repository-url>
cd taquin
make release
```

### Fedora/CentOS/RHEL
```bash
# Install dependencies
sudo dnf install gcc make SDL2-devel
# or for older versions: sudo yum install gcc make SDL2-devel

# Clone and build
git clone <repository-url>
cd taquin
make release
```

### Arch Linux
```bash
# Install dependencies
sudo pacman -S gcc make sdl2

# Clone and build
git clone <repository-url>
cd taquin
make release
```

## 🍎 macOS Installation

### Using Homebrew (Recommended)
```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install sdl2

# Clone and build
git clone <repository-url>
cd taquin
make release
```

### Using MacPorts
```bash
# Install SDL2
sudo port install libsdl2

# Clone and build
git clone <repository-url>
cd taquin
make release
```

## 🔧 Build Options

### Available Make Targets
```bash
make release    # Build optimized version
make debug      # Build with debug symbols
make clean      # Remove build files
make run        # Build and run the game
make package    # Create distribution package
make install    # Install system-wide (Unix-like only)
make help       # Show all available targets
```

### Custom SDL2 Paths

If SDL2 is installed in a custom location:

```bash
# Example for custom installation
make SDL2_CFLAGS="-I/custom/path/include" SDL2_LIBS="-L/custom/path/lib -lSDL2main -lSDL2"
```

## 🚀 Running the Game

After successful compilation:

```bash
# Linux/macOS
./bin/taquin

# Windows
./bin/taquin.exe
# or double-click the executable
```

## 🐛 Troubleshooting

### Common Issues

1. **SDL2 not found**
   - Ensure SDL2 development libraries are installed
   - Check that include and library paths are correct
   - On Windows, verify the paths in the Makefile match your SDL2 installation

2. **Compilation errors**
   - Make sure you have a C99-compatible compiler
   - Check that all source files are present
   - Verify that header files can be found

3. **Runtime errors**
   - Ensure SDL2 runtime libraries are available
   - On Windows, make sure SDL2.dll is in the same directory as the executable
   - Check that image files are in the correct `images/` directory

4. **Permission errors (Linux/macOS)**
   - Use `sudo` for system-wide installation
   - Or install to a user directory instead

### Getting Help

If you encounter issues:

1. Check the error messages carefully
2. Verify your SDL2 installation
3. Try building with debug symbols: `make debug`
4. Check our [Issues page](https://github.com/yourusername/taquin/issues)
5. Create a new issue with:
   - Your operating system and version
   - Compiler version (`gcc --version`)
   - SDL2 version
   - Complete error messages

## 📦 Distribution

### Creating Packages

To create a distribution package:

```bash
make package
```

This will create a platform-specific archive containing:
- The game executable
- Required assets (images)
- Documentation
- Runtime libraries (Windows only)

### Installing for Others

For system-wide installation (Linux/macOS):

```bash
sudo make install
```

For Windows, copy the contents of the package to the desired location.

---

**Happy Gaming! 🎮**
