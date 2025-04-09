cmake_minimum_required(VERSION 3.10)
project(CAM)

# Enable debugging output
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

# Enable Qt's meta-object compiler for signals/slots
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Generate compile_commands.json" FORCE)

# Find OpenCASCADE
set(OpenCASCADE_DIR "/usr/local/Cellar/opencascade/7.9.0/lib/cmake/opencascade")
find_package(OpenCASCADE REQUIRED)

message(STATUS "OpenCASCADE_FOUND: ${OpenCASCADE_FOUND}")
message(STATUS "OpenCASCADE_INCLUDE_DIR: ${OpenCASCADE_INCLUDE_DIR}")
message(STATUS "OpenCASCADE_LIBRARY_DIR: ${OpenCASCADE_LIBRARY_DIR}")
message(STATUS "OpenCASCADE_LIBRARIES: ${OpenCASCADE_LIBRARIES}")

include_directories(${OpenCASCADE_INCLUDE_DIR})
link_directories(${OpenCASCADE_LIBRARY_DIR})

# CLI App
add_executable(cam_cli
    src/main_cli.cpp
    src/geometry_utils.cpp
)

add_executable(cam_gui
    src/main_gui.cpp
    src/main_window.cpp
    src/viewer/OCCTWidget.cpp
    src/geometry_utils.cpp
)

# CLI (minimal link, OpenCascade only)
target_link_libraries(cam_cli ${OpenCASCADE_LIBRARIES})

# GUI (adds Qt6 too)
set(CMAKE_PREFIX_PATH "/usr/local/opt/qt/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

message(STATUS "Qt6_FOUND: ${Qt6_FOUND}")
message(STATUS "Qt6_DIR: ${Qt6_DIR}")

target_link_libraries(cam_gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    ${OpenCASCADE_LIBRARIES}
)
