# GTK (gtkmm) Basic Example

A modern C++ GUI application using gtkmm (the C++ bindings for GTK), demonstrating native Linux desktop integration.

## Features
- Text input with placeholder text
- Add and Clear buttons
- Scrollable text display area
- Confirmation dialogs
- Status updates
- Frame-based organization
- Modern GTK3 styling
- Keyboard shortcuts (Enter to add)
- Native GNOME/Linux look and feel

## Requirements
- GTK3 development libraries
- gtkmm-3.0 (C++ bindings)
- pkg-config
- CMake 3.16+
- C++17 compiler

## Installation & Build

### Ubuntu/Debian
```bash
sudo apt-get install libgtkmm-3.0-dev pkg-config
mkdir build && cd build
cmake ..
make
./gtkmm_example
```

### Fedora/CentOS/RHEL
```bash
sudo dnf install gtkmm30-devel pkgconfig
mkdir build && cd build
cmake ..
make
./gtkmm_example
```

### Arch Linux
```bash
sudo pacman -S gtkmm3 pkgconf
mkdir build && cd build
cmake ..
make
./gtkmm_example
```

### macOS (with Homebrew)
```bash
brew install gtkmm3 pkg-config
mkdir build && cd build
cmake ..
make
./gtkmm_example
```

## Key GTK/gtkmm Concepts
- **Containers**: VBox, HBox, Frame for layout organization
- **Widgets**: Entry, Button, TextView, Label, ScrolledWindow
- **Signals**: Event handling with sigc++ library
- **RefPtr**: Smart pointers for GTK objects
- **TextBuffer**: Model-view pattern for text display
- **MessageDialog**: Standard system dialogs
- **Application**: Modern GTK application framework
- **Native Theming**: Integrates with system theme automatically