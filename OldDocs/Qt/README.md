# Qt Basic UI Example

A simple Qt application demonstrating basic UI functionality including widgets, layouts, and signal-slot connections.

## Features
- Text input field with placeholder text
- Add and Clear buttons
- Text display area
- Message box for validation
- Keyboard shortcuts (Enter to add text)

## Requirements
- Qt6 (Core and Widgets modules)
- CMake 3.16+
- C++17 compiler

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make
./qt_example
```

## Key Qt Concepts Demonstrated
- **Widgets**: QLabel, QLineEdit, QPushButton, QTextEdit
- **Layouts**: QVBoxLayout, QHBoxLayout for responsive design
- **Signals & Slots**: Event handling system
- **Styling**: Basic CSS-like styling with setStyleSheet()
- **MOC**: Meta-Object Compiler for Qt's introspection system