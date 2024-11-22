# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(AdaptiveCacheProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required Qt5 modules
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

# Define the source files
set(SOURCES
    source/main.cpp
    source/main_window.cpp
    source/database_handler.cpp
    source/splay_tree.cpp
)

# Define the header files
set(HEADERS
    include/main_window.h
    include/database_handler.h
    include/splay_tree.h
)

# Include the UI file for Qt Designer
set(UI_FILES
    source/main_window.ui
)

# Automatically process the .ui file with Qt's uic
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# Add Qt MOC processing for header files
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
)

# Add the executable target
add_executable(adaptive_cache_project
    ${SOURCES}
    ${MOC_SOURCES}
    ${UI_HEADERS}
)

# Link against Qt5 libraries and SQLite3
target_link_libraries(adaptive_cache_project Qt5::Widgets Qt5::Core sqlite3)

# Copy the database file to the build directory
configure_file(assets/data.db ${CMAKE_BINARY_DIR}/data.db COPYONLY)

# Specify the output directory for the executable
set_target_properties(adaptive_cache_project PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
