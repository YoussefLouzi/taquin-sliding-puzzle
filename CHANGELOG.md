# Changelog

All notable changes to the Taquin - Sliding Puzzle Game project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.0.0] - 2024-01-XX

### Added
- **Complete code refactoring** with modular architecture
- **Multiple difficulty levels**: 3×3, 4×4, and 5×5 grids
- **Smooth tile animations** during moves
- **Comprehensive scoring system** with move counter and timer
- **Best score tracking** for each difficulty level
- **Professional game states** (Menu, Playing, Win, Paused)
- **Cross-platform Makefile** for Windows, Linux, and macOS
- **Comprehensive README.md** with detailed documentation
- **MIT License** for open-source distribution
- **Build scripts** for easy compilation
- **Error handling** and memory management improvements
- **Code documentation** and inline comments

### Changed
- **Complete rewrite** of the original codebase
- **Improved graphics rendering** with better visual feedback
- **Enhanced user interface** with state-based navigation
- **Better input handling** with mouse and keyboard support
- **Optimized game logic** with proper win condition checking
- **Professional code organization** with separate modules

### Fixed
- **Memory leaks** in texture management
- **Inconsistent coordinate systems** between screen and board
- **Win condition bugs** in the original implementation
- **Resource cleanup** on game exit
- **Cross-platform compatibility** issues

### Technical Improvements
- **Modular design** with separate files for different concerns
- **Proper header guards** and function declarations
- **Consistent coding style** and formatting
- **Error handling** throughout the codebase
- **Resource management** with proper cleanup
- **Platform detection** in build system

## [1.0.0] - Original Version

### Features
- Basic sliding puzzle game
- 3×3 and 4×4 grid support
- Mouse click controls
- Simple menu system
- Basic win detection
- SDL2 graphics

### Known Issues (Fixed in 2.0.0)
- Memory leaks in texture handling
- Inconsistent code organization
- Limited error handling
- Platform-specific build issues
- No scoring or statistics
- Basic user interface

---

## Future Roadmap

### Planned Features for v2.1.0
- **Sound effects** and background music
- **Hint system** to show possible moves
- **Save/Load game state** functionality
- **Custom images** for tiles
- **Online leaderboards** (optional)
- **Accessibility features** for better usability

### Planned Features for v2.2.0
- **AI solver** with step-by-step solution
- **Multiple puzzle types** (different shapes)
- **Themes and customization** options
- **Multiplayer support** (local)
- **Achievement system**

### Long-term Goals
- **Mobile version** (Android/iOS)
- **Web version** using Emscripten
- **3D graphics** option
- **VR support** for immersive experience

---

## Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details on how to submit improvements, bug fixes, and new features.

## Support

For support, bug reports, or feature requests, please visit our [GitHub Issues](https://github.com/yourusername/taquin/issues) page.
