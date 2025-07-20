# Contributing to SDL3Lite

Thank you for your interest in contributing to SDL3Lite! This document provides guidelines and information for contributors.

## 🎯 Project Goals

- **Legacy Support**: Maintain compatibility with older systems (Windows 95+, ancient compilers)
- **Portability**: Keep the codebase portable across platforms and architectures
- **Simplicity**: Provide a lightweight alternative to full SDL3
- **API Compatibility**: Stay compatible with SDL3 API where possible

## 🛠️ Development Environment

### Requirements
- **C++ Standard**: C++98 (strict requirement)
- **Compilers**: GCC 3.0+, Visual C++ 6.0+, Clang 3.0+
- **Build System**: CMake 3.0+

### Coding Standards

#### C++98 Compliance
- **No C++11+ features**: No `auto`, `nullptr`, lambdas, range-based for loops
- **Use classic syntax**: `for (size_t i = 0; i < size; ++i)`
- **Memory management**: Manual memory management, no smart pointers
- **Headers**: Use `<cstdio>` instead of `<iostream>` for better compatibility

#### Style Guidelines
```cpp
// Naming conventions
class ClassName;           // PascalCase for classes
void functionName();       // camelCase for functions  
int member_variable;       // snake_case for members
#define MACRO_NAME         // UPPER_CASE for macros

// Indentation: 4 spaces (no tabs)
if (condition) {
    doSomething();
}

// Pointer style
int* ptr;                  // Asterisk with type
ptr = NULL;                // Use NULL, not nullptr

// Include order
#include <SDL3/SDL.h>      // Project headers first
#include <stdio.h>         // System headers after
```

#### Memory Management
```cpp
// Always check allocations
T* ptr = static_cast<T*>(malloc(sizeof(T) * count));
if (!ptr) {
    // Handle allocation failure
    return false;
}

// Use placement new for non-POD types
new(ptr) T();

// Manual cleanup
ptr->~T();
free(ptr);
```

## 📝 Contribution Process

### 1. Fork and Clone
```bash
git clone https://github.com/your-username/SDL3Lite.git
cd SDL3Lite
```

### 2. Create Feature Branch
```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/bug-description
```

### 3. Development Workflow

#### Testing Your Changes
```bash
# Build and test
cmake -Bout -DCMAKE_BUILD_TYPE=Debug
cd out
make
./Tests

# Test examples
./Multiple
./OpenGL1
./Software
```

#### Platform Testing
- **Windows**: Test on oldest available system (XP minimum)
- **Linux**: Test on Ubuntu 14.04 or CentOS 6 if possible
- **Compilers**: Test with GCC 4.8 and Visual Studio 2005 minimum

### 4. Commit Guidelines
```bash
# Use descriptive commit messages
git commit -m "Fix memory leak in Vector::deallocate"
git commit -m "Add support for 16-bit color formats"
git commit -m "Improve error handling in window creation"
```

### 5. Pull Request

#### Before Submitting
- [ ] Code compiles without warnings on GCC and MSVC
- [ ] All existing tests pass
- [ ] New functionality includes tests
- [ ] Documentation updated if needed
- [ ] No memory leaks (check with Valgrind on Linux)

#### PR Description Template
```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Tested on Windows
- [ ] Tested on Linux
- [ ] All examples work
- [ ] Tests pass

## Platform Compatibility
- [ ] Compiles with GCC 4.8+
- [ ] Compiles with Visual C++ 2005+
- [ ] No C++11+ features used
```

## 🧪 Testing

### Running Tests
```bash
# Build tests
make Tests

# Run all tests
./Tests

# Manual testing with examples
./App
./GL1_Triangle
./textures2
```

### Adding Tests
```cpp
// In Tests.cpp
void TestNewFeature()
{
    // Arrange
    SDL_Window* window = SDL_CreateWindow("Test", 640, 480, SDL_WINDOW_OPENGL);
    
    // Act & Assert
    SDL_TEST(window != NULL);
    SDL_TEST(SDL_GetWindowSize(window) == Vec2i(640, 480));
    
    // Cleanup
    SDL_DestroyWindow(window);
}

// Add to main()
int main()
{
    // ... existing tests ...
    TestNewFeature();
    return 0;
}
```

## 🚫 What NOT to Do

### Forbidden Features (C++11+)
- `auto` keyword
- `nullptr` (use `NULL`)
- Range-based for loops
- Lambda expressions
- `std::shared_ptr`, `std::unique_ptr`
- Initializer lists
- `override`, `final` keywords

### Avoid Dependencies
- Don't add new external dependencies
- Prefer self-contained implementations
- Avoid modern STL features

### Platform-Specific Code
- Keep platform code in separate folders (`Win32/`, `Unix/`)
- Use `#ifdef` sparingly and document
- Test on actual target platforms when possible

## 📚 Documentation

### Code Documentation
```cpp
/**
 * Creates a new window with specified parameters
 * @param title Window title (must not be NULL)
 * @param width Window width in pixels (must be > 0)  
 * @param height Window height in pixels (must be > 0)
 * @param flags Window creation flags
 * @return Window pointer on success, NULL on failure
 * @note Caller is responsible for calling SDL_DestroyWindow()
 */
SDL_Window* SDL_CreateWindow(const char* title, int width, int height, SDL_WindowFlags flags);
```

### Examples
- Include complete, runnable examples
- Add comments explaining non-obvious parts
- Show proper cleanup and error handling

## 🐛 Bug Reports

### Good Bug Report
```markdown
**Environment:**
- OS: Windows XP SP3
- Compiler: Visual C++ 2005
- SDL3Lite version: v0.1.0

**Expected Behavior:**
Window should be created successfully

**Actual Behavior:**
SDL_CreateWindow returns NULL

**Steps to Reproduce:**
1. Call SDL_Init(SDL_INIT_VIDEO)
2. Call SDL_CreateWindow("Test", 640, 480, SDL_WINDOW_OPENGL)
3. Check return value

**Additional Info:**
SDL_GetError() returns "Failed to create OpenGL context"
```

## 💡 Feature Requests

Consider:
- Does it fit the project scope (basic 2D graphics)?
- Can it be implemented in C++98?
- Is it essential for the MVP?
- Does it maintain API compatibility with SDL3?

## 🏷️ Labels and Milestones

### Issue Labels
- `bug` - Something is broken
- `enhancement` - New feature request
- `help wanted` - Good for new contributors
- `platform:windows` - Windows-specific issue
- `platform:linux` - Linux-specific issue
- `compatibility` - C++98/compiler compatibility issue

### Priority Labels
- `priority:critical` - Crashes, data loss
- `priority:high` - Blocks development
- `priority:medium` - Important but not blocking
- `priority:low` - Nice to have

## 🤝 Community

- Be respectful and constructive
- Help newcomers understand the codebase
- Focus on code quality and compatibility
- Share knowledge about legacy systems

Thank you for contributing to SDL3Lite! 🎉