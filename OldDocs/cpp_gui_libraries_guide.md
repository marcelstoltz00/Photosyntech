# C++ GUI Libraries Guide

Here's a breakdown of the main C++ GUI libraries:

## Popular Options

**Qt** - The industry standard
- Most comprehensive and professional
- Excellent documentation and huge community
- Cross-platform (Windows, Mac, Linux, mobile)
- Comes with Qt Creator IDE
- Uses "signals and slots" for event handling
- Has a learning curve but very powerful

**Dear ImGui** - Immediate mode GUI
- Extremely beginner-friendly
- Perfect for tools, debug interfaces, or game UIs
- No complex setup, just include and go
- Not for traditional desktop applications
- Renders inside your OpenGL/DirectX/Vulkan window

**wxWidgets** - Native look and feel
- Uses native OS controls
- Good documentation
- Lighter weight than Qt
- More C-like API (less modern C++)

**GTK (gtkmm)** - Linux-focused
- Popular on Linux, works on other platforms
- Modern C++ bindings with gtkmm
- Good if targeting Linux primarily


## My Recommendation

**For a beginner, I'd recommend starting with Dear ImGui** if you're making tools, prototypes, or game-related UIs. It's the easiest to get running and you'll have something on screen in minutes.

**If you need a traditional desktop application, go with Qt**. Despite the steeper learning curve, the investment pays off with better tools, documentation, and job market relevance. Start with Qt Widgets (not QML) as it's more straightforward.

What kind of application are you building? That would help me give you more specific advice.

## Step-by-Step Instructions to Run Each GUI Library

**Prerequisites**: Install cmake first on all platforms:

**macOS:**
```bash
brew install cmake
```

**Ubuntu/Debian:**
```bash
sudo apt install cmake build-essential
```

**Fedora/RHEL:**
```bash
sudo dnf install cmake gcc-c++
```

### 1. Dear ImGui Example (Easiest - Start Here!)

**macOS:**
```bash
cd DearImGui/
brew install glfw
mkdir -p build && cd build
cmake ..
make
./imgui_example
```

**Ubuntu/Debian:**
```bash
cd DearImGui/
sudo apt install libglfw3-dev libgl1-mesa-dev
mkdir -p build && cd build
cmake ..
make
./imgui_example
```

**Fedora:**
```bash
cd DearImGui/
sudo dnf install glfw-devel mesa-libGL-devel
mkdir -p build && cd build
cmake ..
make
./imgui_example
```

**Alternative - Direct compilation (macOS only):**
```bash
cd DearImGui/
g++ -std=c++17 -DGL_SILENCE_DEPRECATION -I. -Ibackends -I/opt/homebrew/opt/glfw/include main.cpp imgui*.cpp backends/imgui_impl_glfw.cpp backends/imgui_impl_opengl3.cpp -L/opt/homebrew/opt/glfw/lib -lglfw -framework OpenGL -o imgui_example
./imgui_example
```

### 2. Qt Example

**macOS:**
```bash
cd Qt/
brew install qt6
mkdir -p build && cd build
cmake ..
make
./qt_example
```

**Ubuntu/Debian:**
```bash
cd Qt/
sudo apt install qt6-base-dev qt6-tools-dev
mkdir -p build && cd build
cmake ..
make
./qt_example
```

**Fedora:**
```bash
cd Qt/
sudo dnf install qt6-qtbase-devel qt6-qttools-devel
mkdir -p build && cd build
cmake ..
make
./qt_example
```

### 3. wxWidgets Example

**macOS:**
```bash
cd wxWidgets/
brew install wxwidgets
mkdir -p build && cd build
cmake ..
make
./wxwidgets_example
```

**Ubuntu/Debian:**
```bash
cd wxWidgets/
sudo apt install libwxgtk3.0-gtk3-dev
mkdir -p build && cd build
cmake ..
make
./wxwidgets_example
```

**Fedora:**
```bash
cd wxWidgets/
sudo dnf install wxGTK3-devel
mkdir -p build && cd build
cmake ..
make
./wxwidgets_example
```

### 4. GTK (gtkmm) Example

**macOS:**
```bash
cd GTK_gtkmm/
brew install gtkmm3 pkg-config
mkdir -p build && cd build
cmake ..
make
./gtkmm_example
```

**Ubuntu/Debian:**
```bash
cd GTK_gtkmm/
sudo apt install libgtkmm-3.0-dev pkg-config
mkdir -p build && cd build
cmake ..
make
./gtkmm_example
```

**Fedora:**
```bash
cd GTK_gtkmm/
sudo dnf install gtkmm30-devel pkgconfig
mkdir -p build && cd build
cmake ..
make
./gtkmm_example
```

## Quick Start Order (Easiest to Hardest)
1. **Dear ImGui** - Minimal setup, immediate results
2. **Qt** - Well-documented, professional grade
3. **wxWidgets** - Native OS look and feel
4. **GTK (gtkmm)** - Linux-focused, more setup needed

## Troubleshooting

### Common Issues

**Dear ImGui on macOS:**
- If you get OpenGL version errors, the code automatically uses OpenGL 3.2+ for macOS compatibility
- Use the direct compilation option if CMake takes too long

**Linux package names vary:**
- **Ubuntu/Debian**: Use `apt` commands as shown
- **Fedora/RHEL/CentOS**: Use `dnf` commands as shown
- **Arch Linux**: Use `pacman -S` instead (e.g., `pacman -S glfw-wayland cmake`)

**Missing CMake:**
- Install cmake first before trying any examples
- On macOS: `brew install cmake`
- On Ubuntu: `sudo apt install cmake build-essential`

**Qt6 installation time:**
- Qt6 can take 10-15 minutes to install via Homebrew due to many dependencies
- This is normal - be patient!


**CMake configuration errors:**
- If you see "keyword signature" errors, the CMakeLists.txt files have been fixed
- Try deleting the build directory and recreating it: `rm -rf build && mkdir build && cd build`

### What Each Example Demonstrates
- **Text input and display**
- **Button handling and events**
- **Layout management**
- **Basic styling**
- **Cross-platform window creation**

All examples create the same basic functionality using each library's unique approach!