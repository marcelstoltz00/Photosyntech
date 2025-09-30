# Dear ImGui Basic Example

An immediate mode GUI application demonstrating Dear ImGui's core functionality with OpenGL and GLFW.

## Features
- Text input and display
- Dynamic list of text entries
- Interactive controls (slider, color picker, counter)
- Built-in demo window
- Real-time frame rate display
- Clean immediate mode rendering

## Requirements
- GLFW3
- OpenGL 3.0+
- CMake 3.16+
- C++17 compiler

## Build Instructions

### Ubuntu/Debian
```bash
sudo apt-get install libglfw3-dev libgl1-mesa-dev
mkdir build && cd build
cmake ..
make
./imgui_example
```

### macOS (with Homebrew)
```bash
brew install glfw
mkdir build && cd build
cmake ..
make
./imgui_example
```

### Windows (with vcpkg)
```bash
vcpkg install glfw3 opengl
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

## Key Dear ImGui Concepts
- **Immediate Mode**: UI is rebuilt every frame
- **No State Management**: ImGui handles all widget states internally
- **Immediate Feedback**: Changes are visible instantly
- **Debug-Friendly**: Perfect for tools and debugging interfaces
- **Minimal Setup**: No complex layouts or event systems needed
- **Platform Agnostic**: Renders to any graphics API