cmake_minimum_required(VERSION 3.16)
project(GtkmmExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# Find gtkmm-3.0
pkg_check_modules(GTKMM gtkmm-3.0)

if(GTKMM_FOUND)
    # Include directories
    include_directories(${GTKMM_INCLUDE_DIRS})

    # Link directories
    link_directories(${GTKMM_LIBRARY_DIRS})

    # Add compiler flags
    add_definitions(${GTKMM_CFLAGS_OTHER})

    # Create executable
    add_executable(gtkmm_example main.cpp)

    # Link libraries
    target_link_libraries(gtkmm_example ${GTKMM_LIBRARIES})

    # Set compiler flags
    target_compile_options(gtkmm_example PRIVATE ${GTKMM_CFLAGS_OTHER})

else()
    message(FATAL_ERROR "gtkmm-3.0 not found! Please install gtkmm development libraries.")
endif()