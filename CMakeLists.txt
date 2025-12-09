cmake_minimum_required(VERSION 3.21)

project(vibevidz VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Declare projectM
FetchContent_Declare(
  projectM
  GIT_REPOSITORY https://github.com/projectM-visualizer/projectm.git
  GIT_TAG        v4.1.0 # Using a stable release tag
)

# Make projectM available to our project
FetchContent_MakeAvailable(projectM)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Define the executable
add_executable(vibevidz src/main.cpp)

# Link against Qt6 and projectM.
# The target name for projectM is typically the project name itself, or libprojectM,
# or projectM::projectM depending on how it's defined in its CMakeLists.txt.
# Based on earlier investigations, 'projectM' was found to be a valid target.
target_link_libraries(vibevidz PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets projectM)
