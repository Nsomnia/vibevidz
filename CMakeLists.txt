cmake_minimum_required(VERSION 3.21)

project(vibevidz VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. FIND QT6 FIRST
# Added 'Multimedia' for audio capture and 'OpenGLWidgets' for the widget.
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets Multimedia)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 2. CONFIGURE PROJECTM
include(FetchContent)

# Disable unnecessary parts of projectM to speed up build
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(ENABLE_SDL OFF CACHE BOOL "" FORCE)
set(ENABLE_EMSCRIPTEN OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  projectM
  GIT_REPOSITORY https://github.com/projectM-visualizer/projectm.git
  GIT_TAG        v4.1.0
)

# This downloads and adds projectM targets to your build
FetchContent_MakeAvailable(projectM)

# 3. DEFINE EXECUTABLE
add_executable(vibevidz
  src/main.cpp
  src/MainWindow.h
  src/MainWindow.cpp
  src/ProjectMWidget.h
  src/ProjectMWidget.cpp
)

# Pass the projectM source directory to C++ so we can find default resources (fonts/textures)
target_compile_definitions(vibevidz PRIVATE PROJECTM_RESOURCES_PATH="${projectM_SOURCE_DIR}/src/libprojectM/resources")

# 4. LINK LIBRARIES
target_link_libraries(vibevidz PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Multimedia
    projectM      # Link against the main library
)
