# Changelog

All notable changes to SDL3Lite will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Improved README with comprehensive documentation
- Contributing guidelines for developers
- Better error handling throughout the codebase
- Input validation for all public API functions

### Fixed
- Critical memory management bug in Vector::deallocate
- Memory leaks in window and renderer creation
- Null pointer dereferences in core functions

### Changed
- Enhanced build system with better compiler detection
- Improved examples with better error handling
- More robust platform detection in CMake

## [0.1.0-alpha] - 2024-01-XX

### Added
- Basic window management system
- OpenGL 1.x rendering support
- Software rendering fallback  
- BMP texture loading
- Event handling system
- Cross-platform timer support
- Basic 2D rendering primitives (rectangles, lines)
- Platform support for Windows 95+ and Linux
- Examples demonstrating core functionality

### Core Features
- `SDL_Init()` and `SDL_Quit()` for library initialization
- `SDL_CreateWindow()` and `SDL_DestroyWindow()` for window management
- `SDL_CreateRenderer()` and `SDL_DestroyRenderer()` for rendering
- `SDL_PollEvent()` for event handling
- Basic drawing functions (clear, present, draw primitives)

### Platform Support
- Windows: Win32 API implementation
- Linux: X11/XLib implementation
- OpenGL: Hardware-accelerated rendering
- Software: Pure CPU rendering fallback

### Build System
- CMake build system with platform detection
- Support for Visual C++ 6.0+, GCC 3.0+
- Automatic dependency detection

### Examples
- Basic window creation (`App.c`)
- OpenGL triangle rendering (`GL1_Triangle.c`)
- Software rendering (`Software.c`)
- Texture loading and display (`textures2.c`)
- Multiple window management (`Multiple.c`)

## [0.0.1] - Initial Development

### Added
- Project structure and initial codebase
- Basic cross-platform abstraction layer
- Core container classes (Vector, String, RingBuffer)
- Initial window system implementation
- Basic OpenGL context creation
- Software rendering foundation

---

## Version Numbering

SDL3Lite follows semantic versioning:
- **MAJOR**: Incompatible API changes
- **MINOR**: New functionality (backwards compatible)
- **PATCH**: Bug fixes (backwards compatible)

## Release Types

- **alpha**: Early development, may have significant bugs
- **beta**: Feature complete, ready for testing
- **rc**: Release candidate, production ready pending final testing
- **(none)**: Stable release

## Compatibility Promise

- **API**: Minor versions maintain API compatibility
- **ABI**: Patch versions maintain ABI compatibility  
- **Platform**: New platforms may be added in minor versions
- **C++98**: All versions maintain C++98 compatibility