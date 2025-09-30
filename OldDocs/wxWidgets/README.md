# wxWidgets Basic Example

A native-looking GUI application demonstrating wxWidgets' core functionality with native OS controls.

## Features
- Text input with hint text
- Add and Clear buttons with confirmation dialog
- Multi-line text display area
- Menu bar with File and Help menus
- Status bar with real-time updates
- Keyboard shortcuts (Ctrl+N, Ctrl+Q, Enter)
- Native OS look and feel
- Message dialogs for user interaction

## Requirements
- wxWidgets 3.0+ development libraries
- CMake 3.16+
- C++17 compiler

## Installation & Build

### Ubuntu/Debian
```bash
sudo apt-get install libwxgtk3.0-gtk3-dev
mkdir build && cd build
cmake ..
make
./wxwidgets_example
```

### macOS (with Homebrew)
```bash
brew install wxwidgets
mkdir build && cd build
cmake ..
make
./wxwidgets_example
```

### Windows (with vcpkg)
```bash
vcpkg install wxwidgets
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

### Fedora/CentOS/RHEL
```bash
sudo dnf install wxGTK3-devel  # or wxGTK-devel for older versions
mkdir build && cd build
cmake ..
make
./wxwidgets_example
```

## Key wxWidgets Concepts
- **Native Controls**: Uses actual OS widgets for native look/feel
- **Sizers**: Flexible layout management system
- **Event Binding**: Connect events to handler functions
- **Dialogs**: Built-in message boxes and custom dialogs
- **Menu System**: Standard menu bar and popup menus
- **Status Bar**: Information display at bottom of window
- **Cross-Platform**: Same code works on Windows, macOS, and Linux