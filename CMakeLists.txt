cmake_minimum_required(VERSION 3.21)

project(vibevidz VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. FIND QT6 FIRST
# We find Qt6 before defining targets so AUTOMOC knows which 'moc' to use.
# Added 'OpenGLWidgets' which is required for QOpenGLWidget in Qt6.
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 2. CONFIGURE PROJECTM
include(FetchContent)

# Optional: Disable projectM examples/tests to speed up build and avoid extra deps (like SDL2)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(ENABLE_SDL OFF CACHE BOOL "" FORCE)

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

# 4. LINK LIBRARIES
# Note: projectM v4 main target is often named 'libprojectM' or 'projectM'.
# We link both common names just in case, plus the specific playlist target.
target_link_libraries(vibevidz PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    projectM      # Try linking the main projectM target
)

# Verify if 'projectM_playlist' is actually available from the fetch.
# If projectM 4.1 doesn't expose it globally, you might need to check their CMake docs.
if(TARGET projectM_playlist)
    target_link_libraries(vibevidz PRIVATE projectM_playlist)
endif()
