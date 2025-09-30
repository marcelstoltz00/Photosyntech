cmake_minimum_required(VERSION 3.16)
project(QtBasicExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt6_standard_project_setup()

qt6_add_executable(qt_example main.cpp)

target_link_libraries(qt_example PRIVATE Qt6::Core Qt6::Widgets)

# Enable automatic MOC (Meta-Object Compiler)
set_target_properties(qt_example PROPERTIES
    AUTOMOC ON
)