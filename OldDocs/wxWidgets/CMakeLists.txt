cmake_minimum_required(VERSION 3.16)
project(wxWidgetsExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})

    add_executable(wxwidgets_example main.cpp)

    target_link_libraries(wxwidgets_example ${wxWidgets_LIBRARIES})

    # Copy wxWidgets DLLs on Windows
    if(WIN32)
        foreach(lib ${wxWidgets_LIBRARIES})
            get_filename_component(lib_dir ${lib} DIRECTORY)
            file(GLOB dll_files "${lib_dir}/*.dll")
            foreach(dll ${dll_files})
                add_custom_command(TARGET wxwidgets_example POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${dll} $<TARGET_FILE_DIR:wxwidgets_example>)
            endforeach()
        endforeach()
    endif()
else()
    message(FATAL_ERROR "wxWidgets not found! Please install wxWidgets development libraries.")
endif()